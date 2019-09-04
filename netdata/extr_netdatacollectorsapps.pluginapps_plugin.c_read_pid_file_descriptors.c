#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct pid_stat {size_t fds_size; TYPE_2__* fds; TYPE_1__* target; int /*<<< orphan*/  pid; int /*<<< orphan*/  comm; void* fds_dirname; } ;
struct pid_fd {int dummy; } ;
struct dirent {char* d_name; scalar_t__ d_ino; } ;
typedef  int ssize_t ;
struct TYPE_6__ {scalar_t__ inode; size_t cache_iterations_counter; scalar_t__ link_hash; size_t cache_iterations_reset; int /*<<< orphan*/  fd; void* filename; } ;
struct TYPE_5__ {scalar_t__ debug_enabled; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  FILENAME_MAX ; 
 int MAX_SPARE_FDS ; 
 int /*<<< orphan*/  cleanup_negative_pid_fds (struct pid_stat*) ; 
 int /*<<< orphan*/  clear_pid_fd (TYPE_2__*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ debug_enabled ; 
 int /*<<< orphan*/  debug_log (char*,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  error (char*,void*) ; 
 int /*<<< orphan*/  file_counter ; 
 int /*<<< orphan*/  file_descriptor_find_or_add (char*,scalar_t__) ; 
 int /*<<< orphan*/  file_descriptor_not_used (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filenames_allocated_counter ; 
 int /*<<< orphan*/  init_pid_fds (struct pid_stat*,size_t,int) ; 
 int /*<<< orphan*/  inodes_changed_counter ; 
 int /*<<< orphan*/  links_changed_counter ; 
 int /*<<< orphan*/  make_all_pid_fds_negative (struct pid_stat*) ; 
 scalar_t__ max_fds_cache_seconds ; 
 int /*<<< orphan*/  netdata_configured_host_prefix ; 
 int /*<<< orphan*/ * opendir (void*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int readlink (void*,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* reallocz (TYPE_2__*,int) ; 
 scalar_t__ simple_hash (char*) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ str2l (char*) ; 
 void* strdupz (char*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ update_every ; 

__attribute__((used)) static inline int read_pid_file_descriptors(struct pid_stat *p, void *ptr) {
    (void)ptr;
#ifdef __FreeBSD__
    int mib[4];
    size_t size;
    struct kinfo_file *fds;
    static char *fdsbuf;
    char *bfdsbuf, *efdsbuf;
    char fdsname[FILENAME_MAX + 1];

    // we make all pid fds negative, so that
    // we can detect unused file descriptors
    // at the end, to free them
    make_all_pid_fds_negative(p);

    mib[0] = CTL_KERN;
    mib[1] = KERN_PROC;
    mib[2] = KERN_PROC_FILEDESC;
    mib[3] = p->pid;

    if (unlikely(sysctl(mib, 4, NULL, &size, NULL, 0))) {
        error("sysctl error: Can't get file descriptors data size for pid %d", p->pid);
        return 0;
    }
    if (likely(size > 0))
        fdsbuf = reallocz(fdsbuf, size);
    if (unlikely(sysctl(mib, 4, fdsbuf, &size, NULL, 0))) {
        error("sysctl error: Can't get file descriptors data for pid %d", p->pid);
        return 0;
    }

    bfdsbuf = fdsbuf;
    efdsbuf = fdsbuf + size;
    while (bfdsbuf < efdsbuf) {
        fds = (struct kinfo_file *)(uintptr_t)bfdsbuf;
        if (unlikely(fds->kf_structsize == 0))
            break;

        // do not process file descriptors for current working directory, root directory,
        // jail directory, ktrace vnode, text vnode and controlling terminal
        if (unlikely(fds->kf_fd < 0)) {
            bfdsbuf += fds->kf_structsize;
            continue;
        }

        // get file descriptors array index
        int fdid = fds->kf_fd;

        // check if the fds array is small
        if (unlikely(fdid >= p->fds_size)) {
            // it is small, extend it

            debug_log("extending fd memory slots for %s from %d to %d", p->comm, p->fds_size, fdid + MAX_SPARE_FDS);

            p->fds = reallocz(p->fds, (fdid + MAX_SPARE_FDS) * sizeof(struct pid_fd));

            // and initialize it
            init_pid_fds(p, p->fds_size, (fdid + MAX_SPARE_FDS) - p->fds_size);
            p->fds_size = fdid + MAX_SPARE_FDS;
        }

        if (unlikely(p->fds[fdid].fd == 0)) {
            // we don't know this fd, get it

            switch (fds->kf_type) {
                case KF_TYPE_FIFO:
                case KF_TYPE_VNODE:
                    if (unlikely(!fds->kf_path[0])) {
                        sprintf(fdsname, "other: inode: %lu", fds->kf_un.kf_file.kf_file_fileid);
                        break;
                    }
                    sprintf(fdsname, "%s", fds->kf_path);
                    break;
                case KF_TYPE_SOCKET:
                    switch (fds->kf_sock_domain) {
                        case AF_INET:
                        case AF_INET6:
                            if (fds->kf_sock_protocol == IPPROTO_TCP)
                                sprintf(fdsname, "socket: %d %lx", fds->kf_sock_protocol, fds->kf_un.kf_sock.kf_sock_inpcb);
                            else
                                sprintf(fdsname, "socket: %d %lx", fds->kf_sock_protocol, fds->kf_un.kf_sock.kf_sock_pcb);
                            break;
                        case AF_UNIX:
                            /* print address of pcb and connected pcb */
                            sprintf(fdsname, "socket: %lx %lx", fds->kf_un.kf_sock.kf_sock_pcb, fds->kf_un.kf_sock.kf_sock_unpconn);
                            break;
                        default:
                            /* print protocol number and socket address */
#if __FreeBSD_version < 1200031
                            sprintf(fdsname, "socket: other: %d %s %s", fds->kf_sock_protocol, fds->kf_sa_local.__ss_pad1, fds->kf_sa_local.__ss_pad2);
#else
                            sprintf(fdsname, "socket: other: %d %s %s", fds->kf_sock_protocol, fds->kf_un.kf_sock.kf_sa_local.__ss_pad1, fds->kf_un.kf_sock.kf_sa_local.__ss_pad2);
#endif
                    }
                    break;
                case KF_TYPE_PIPE:
                    sprintf(fdsname, "pipe: %lu %lu", fds->kf_un.kf_pipe.kf_pipe_addr, fds->kf_un.kf_pipe.kf_pipe_peer);
                    break;
                case KF_TYPE_PTS:
#if __FreeBSD_version < 1200031
                    sprintf(fdsname, "other: pts: %u", fds->kf_un.kf_pts.kf_pts_dev);
#else
                    sprintf(fdsname, "other: pts: %lu", fds->kf_un.kf_pts.kf_pts_dev);
#endif
                    break;
                case KF_TYPE_SHM:
                    sprintf(fdsname, "other: shm: %s size: %lu", fds->kf_path, fds->kf_un.kf_file.kf_file_size);
                    break;
                case KF_TYPE_SEM:
                    sprintf(fdsname, "other: sem: %u", fds->kf_un.kf_sem.kf_sem_value);
                    break;
                default:
                    sprintf(fdsname, "other: pid: %d fd: %d", fds->kf_un.kf_proc.kf_pid, fds->kf_fd);
            }

            // if another process already has this, we will get
            // the same id
            p->fds[fdid].fd = file_descriptor_find_or_add(fdsname, 0);
        }

            // else make it positive again, we need it
            // of course, the actual file may have changed

        else
            p->fds[fdid].fd = -p->fds[fdid].fd;

        bfdsbuf += fds->kf_structsize;
    }
#else
    if(unlikely(!p->fds_dirname)) {
        char dirname[FILENAME_MAX+1];
        snprintfz(dirname, FILENAME_MAX, "%s/proc/%d/fd", netdata_configured_host_prefix, p->pid);
        p->fds_dirname = strdupz(dirname);
    }

    DIR *fds = opendir(p->fds_dirname);
    if(unlikely(!fds)) return 0;

    struct dirent *de;
    char linkname[FILENAME_MAX + 1];

    // we make all pid fds negative, so that
    // we can detect unused file descriptors
    // at the end, to free them
    make_all_pid_fds_negative(p);

    while((de = readdir(fds))) {
        // we need only files with numeric names

        if(unlikely(de->d_name[0] < '0' || de->d_name[0] > '9'))
            continue;

        // get its number
        int fdid = (int) str2l(de->d_name);
        if(unlikely(fdid < 0)) continue;

        // check if the fds array is small
        if(unlikely((size_t)fdid >= p->fds_size)) {
            // it is small, extend it

            debug_log("extending fd memory slots for %s from %d to %d"
                    , p->comm
                    , p->fds_size
                    , fdid + MAX_SPARE_FDS
            );

            p->fds = reallocz(p->fds, (fdid + MAX_SPARE_FDS) * sizeof(struct pid_fd));

            // and initialize it
            init_pid_fds(p, p->fds_size, (fdid + MAX_SPARE_FDS) - p->fds_size);
            p->fds_size = (size_t)fdid + MAX_SPARE_FDS;
        }

        if(unlikely(p->fds[fdid].fd < 0 && de->d_ino != p->fds[fdid].inode)) {
            // inodes do not match, clear the previous entry
            inodes_changed_counter++;
            file_descriptor_not_used(-p->fds[fdid].fd);
            clear_pid_fd(&p->fds[fdid]);
        }

        if(p->fds[fdid].fd < 0 && p->fds[fdid].cache_iterations_counter > 0) {
            p->fds[fdid].fd = -p->fds[fdid].fd;
            p->fds[fdid].cache_iterations_counter--;
            continue;
        }

        if(unlikely(!p->fds[fdid].filename)) {
            filenames_allocated_counter++;
            char fdname[FILENAME_MAX + 1];
            snprintfz(fdname, FILENAME_MAX, "%s/proc/%d/fd/%s", netdata_configured_host_prefix, p->pid, de->d_name);
            p->fds[fdid].filename = strdupz(fdname);
        }

        file_counter++;
        ssize_t l = readlink(p->fds[fdid].filename, linkname, FILENAME_MAX);
        if(unlikely(l == -1)) {
            // cannot read the link

            if(debug_enabled || (p->target && p->target->debug_enabled))
                error("Cannot read link %s", p->fds[fdid].filename);

            if(unlikely(p->fds[fdid].fd < 0)) {
                file_descriptor_not_used(-p->fds[fdid].fd);
                clear_pid_fd(&p->fds[fdid]);
            }

            continue;
        }
        else
            linkname[l] = '\0';

        uint32_t link_hash = simple_hash(linkname);

        if(unlikely(p->fds[fdid].fd < 0 && p->fds[fdid].link_hash != link_hash)) {
            // the link changed
            links_changed_counter++;
            file_descriptor_not_used(-p->fds[fdid].fd);
            clear_pid_fd(&p->fds[fdid]);
        }

        if(unlikely(p->fds[fdid].fd == 0)) {
            // we don't know this fd, get it

            // if another process already has this, we will get
            // the same id
            p->fds[fdid].fd = file_descriptor_find_or_add(linkname, link_hash);
            p->fds[fdid].inode = de->d_ino;
            p->fds[fdid].link_hash = link_hash;
        }
        else {
            // else make it positive again, we need it
            p->fds[fdid].fd = -p->fds[fdid].fd;
        }

        // caching control
        // without this we read all the files on every iteration
        if(max_fds_cache_seconds > 0) {
            size_t spread = ((size_t)max_fds_cache_seconds > 10) ? 10 : (size_t)max_fds_cache_seconds;

            // cache it for a few iterations
            size_t max = ((size_t) max_fds_cache_seconds + (fdid % spread)) / (size_t) update_every;
            p->fds[fdid].cache_iterations_reset++;

            if(unlikely(p->fds[fdid].cache_iterations_reset % spread == (size_t) fdid % spread))
                p->fds[fdid].cache_iterations_reset++;

            if(unlikely((fdid <= 2 && p->fds[fdid].cache_iterations_reset > 5) ||
                        p->fds[fdid].cache_iterations_reset > max)) {
                // for stdin, stdout, stderr (fdid <= 2) we have checked a few times, or if it goes above the max, goto max
                p->fds[fdid].cache_iterations_reset = max;
            }

            p->fds[fdid].cache_iterations_counter = p->fds[fdid].cache_iterations_reset;
        }
    }

    closedir(fds);
#endif
    cleanup_negative_pid_fds(p);

    return 1;
}