#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  usec_t ;
struct statfs {char* f_mntonname; char* f_fstypename; int f_flags; int f_blocks; char* f_mntfromname; int f_bsize; int f_bavail; int f_bfree; int f_files; int f_ffree; } ;
struct mount_point {int updated; int configured; int enabled; scalar_t__ do_space; scalar_t__ do_inodes; int /*<<< orphan*/  collected; void* st_inodes; void* rd_inodes_used; void* rd_inodes_avail; void* st_space; void* rd_space_reserved; void* rd_space_used; void* rd_space_avail; } ;
typedef  int /*<<< orphan*/  collected_number ;
typedef  int /*<<< orphan*/  SIMPLE_PATTERN ;

/* Variables and functions */
 scalar_t__ CONFIG_BOOLEAN_AUTO ; 
 int CONFIG_BOOLEAN_NO ; 
 scalar_t__ CONFIG_BOOLEAN_YES ; 
 char* CONFIG_SECTION_GETMNTINFO ; 
 int /*<<< orphan*/  DEFAULT_EXCLUDED_FILESYSTEMS ; 
 int /*<<< orphan*/  DELAULT_EXCLUDED_PATHS ; 
 int GIGA_FACTOR ; 
 int /*<<< orphan*/  MNT_NOWAIT ; 
 int MNT_RDONLY ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_DISKSPACE_INODES ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_DISKSPACE_SPACE ; 
 int /*<<< orphan*/  RRDSET_TYPE_STACKED ; 
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 int /*<<< orphan*/  SIMPLE_PATTERN_EXACT ; 
 int /*<<< orphan*/  config_get (char*,char*,int /*<<< orphan*/ ) ; 
 void* config_get_boolean_ondemand (char*,char*,int) ; 
 int /*<<< orphan*/  error (char*) ; 
 struct mount_point* get_mount_point (char*) ; 
 int getmntinfo (struct statfs**,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mount_points_cleanup () ; 
 scalar_t__ mount_points_found ; 
 scalar_t__ netdata_zero_metrics_enabled ; 
 void* rrddim_add (void*,char*,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (void*,void*,int /*<<< orphan*/ ) ; 
 void* rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,char*,char*,char*,char*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (void*) ; 
 int /*<<< orphan*/  rrdset_next (void*) ; 
 int /*<<< orphan*/ * simple_pattern_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ simple_pattern_matches (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snprintfz (char*,int,char*,char*,char*) ; 
 scalar_t__ unlikely (int) ; 

int do_getmntinfo(int update_every, usec_t dt) {
    (void)dt;

#define DELAULT_EXCLUDED_PATHS "/proc/*"
// taken from gnulib/mountlist.c and shortened to FreeBSD related fstypes
#define DEFAULT_EXCLUDED_FILESYSTEMS "autofs procfs subfs devfs none"
#define CONFIG_SECTION_GETMNTINFO "plugin:freebsd:getmntinfo"

    static int enable_new_mount_points = -1;
    static int do_space = -1, do_inodes = -1;
    static SIMPLE_PATTERN *excluded_mountpoints = NULL;
    static SIMPLE_PATTERN *excluded_filesystems = NULL;

    if (unlikely(enable_new_mount_points == -1)) {
        enable_new_mount_points = config_get_boolean_ondemand(CONFIG_SECTION_GETMNTINFO,
                                                              "enable new mount points detected at runtime",
                                                              CONFIG_BOOLEAN_AUTO);

        do_space  = config_get_boolean_ondemand(CONFIG_SECTION_GETMNTINFO, "space usage for all disks",  CONFIG_BOOLEAN_AUTO);
        do_inodes = config_get_boolean_ondemand(CONFIG_SECTION_GETMNTINFO, "inodes usage for all disks", CONFIG_BOOLEAN_AUTO);

        excluded_mountpoints = simple_pattern_create(
                config_get(CONFIG_SECTION_GETMNTINFO, "exclude space metrics on paths",
                           DELAULT_EXCLUDED_PATHS)
                , NULL
                , SIMPLE_PATTERN_EXACT
        );

        excluded_filesystems = simple_pattern_create(
                config_get(CONFIG_SECTION_GETMNTINFO, "exclude space metrics on filesystems",
                           DEFAULT_EXCLUDED_FILESYSTEMS)
                , NULL
                , SIMPLE_PATTERN_EXACT
        );
    }

    if (likely(do_space || do_inodes)) {
        struct statfs *mntbuf;
        int mntsize;

        // there is no mount info in sysctl MIBs
        if (unlikely(!(mntsize = getmntinfo(&mntbuf, MNT_NOWAIT)))) {
            error("FREEBSD: getmntinfo() failed");
            do_space = 0;
            error("DISABLED: disk_space.* charts");
            do_inodes = 0;
            error("DISABLED: disk_inodes.* charts");
            error("DISABLED: getmntinfo module");
            return 1;
        } else {
            int i;

            mount_points_found = 0;

            for (i = 0; i < mntsize; i++) {
                char title[4096 + 1];

                struct mount_point *m = get_mount_point(mntbuf[i].f_mntonname);
                m->updated = 1;
                mount_points_found++;

                if (unlikely(!m->configured)) {
                    char var_name[4096 + 1];

                    // this is the first time we see this filesystem

                    // remember we configured it
                    m->configured = 1;

                    m->enabled = enable_new_mount_points;

                    if (likely(m->enabled))
                        m->enabled = !(simple_pattern_matches(excluded_mountpoints, mntbuf[i].f_mntonname)
                                       || simple_pattern_matches(excluded_filesystems, mntbuf[i].f_fstypename));

                    snprintfz(var_name, 4096, "%s:%s", CONFIG_SECTION_GETMNTINFO, mntbuf[i].f_mntonname);
                    m->enabled = config_get_boolean_ondemand(var_name, "enabled", m->enabled);

                    if (unlikely(m->enabled == CONFIG_BOOLEAN_NO))
                        continue;

                    m->do_space  = config_get_boolean_ondemand(var_name, "space usage",  do_space);
                    m->do_inodes = config_get_boolean_ondemand(var_name, "inodes usage", do_inodes);
                }

                if (unlikely(!m->enabled))
                    continue;

                if (unlikely(mntbuf[i].f_flags & MNT_RDONLY && !m->collected))
                    continue;

                // --------------------------------------------------------------------------

                int rendered = 0;

                if (m->do_space == CONFIG_BOOLEAN_YES || (m->do_space == CONFIG_BOOLEAN_AUTO &&
                                                          (mntbuf[i].f_blocks > 2 ||
                                                           netdata_zero_metrics_enabled == CONFIG_BOOLEAN_YES))) {
                    if (unlikely(!m->st_space)) {
                        snprintfz(title, 4096, "Disk Space Usage for %s [%s]",
                                  mntbuf[i].f_mntonname, mntbuf[i].f_mntfromname);
                        m->st_space = rrdset_create_localhost("disk_space",
                                                              mntbuf[i].f_mntonname,
                                                              NULL,
                                                              mntbuf[i].f_mntonname,
                                                              "disk.space",
                                                              title,
                                                              "GiB",
                                                              "freebsd.plugin",
                                                              "getmntinfo",
                                                              NETDATA_CHART_PRIO_DISKSPACE_SPACE,
                                                              update_every,
                                                              RRDSET_TYPE_STACKED
                        );

                        m->rd_space_avail    = rrddim_add(m->st_space, "avail", NULL,
                                                          mntbuf[i].f_bsize, GIGA_FACTOR, RRD_ALGORITHM_ABSOLUTE);
                        m->rd_space_used     = rrddim_add(m->st_space, "used", NULL,
                                                          mntbuf[i].f_bsize, GIGA_FACTOR, RRD_ALGORITHM_ABSOLUTE);
                        m->rd_space_reserved = rrddim_add(m->st_space, "reserved_for_root", "reserved for root",
                                                          mntbuf[i].f_bsize, GIGA_FACTOR, RRD_ALGORITHM_ABSOLUTE);
                    } else
                        rrdset_next(m->st_space);

                    rrddim_set_by_pointer(m->st_space, m->rd_space_avail,    (collected_number) mntbuf[i].f_bavail);
                    rrddim_set_by_pointer(m->st_space, m->rd_space_used,     (collected_number) (mntbuf[i].f_blocks -
                                                                                                 mntbuf[i].f_bfree));
                    rrddim_set_by_pointer(m->st_space, m->rd_space_reserved, (collected_number) (mntbuf[i].f_bfree -
                                                                                                 mntbuf[i].f_bavail));
                    rrdset_done(m->st_space);

                    rendered++;
                }

                // --------------------------------------------------------------------------

                if (m->do_inodes == CONFIG_BOOLEAN_YES || (m->do_inodes == CONFIG_BOOLEAN_AUTO &&
                                                           (mntbuf[i].f_files > 1 ||
                                                            netdata_zero_metrics_enabled == CONFIG_BOOLEAN_YES))) {
                    if (unlikely(!m->st_inodes)) {
                        snprintfz(title, 4096, "Disk Files (inodes) Usage for %s [%s]",
                                  mntbuf[i].f_mntonname, mntbuf[i].f_mntfromname);
                        m->st_inodes = rrdset_create_localhost("disk_inodes",
                                                               mntbuf[i].f_mntonname,
                                                               NULL,
                                                               mntbuf[i].f_mntonname,
                                                               "disk.inodes",
                                                               title,
                                                               "inodes",
                                                               "freebsd.plugin",
                                                               "getmntinfo",
                                                               NETDATA_CHART_PRIO_DISKSPACE_INODES,
                                                               update_every,
                                                               RRDSET_TYPE_STACKED
                        );

                        m->rd_inodes_avail = rrddim_add(m->st_inodes, "avail", NULL, 1, 1, RRD_ALGORITHM_ABSOLUTE);
                        m->rd_inodes_used  = rrddim_add(m->st_inodes, "used",  NULL, 1, 1, RRD_ALGORITHM_ABSOLUTE);
                    } else
                        rrdset_next(m->st_inodes);

                    rrddim_set_by_pointer(m->st_inodes, m->rd_inodes_avail, (collected_number) mntbuf[i].f_ffree);
                    rrddim_set_by_pointer(m->st_inodes, m->rd_inodes_used,  (collected_number) (mntbuf[i].f_files -
                                                                                                mntbuf[i].f_ffree));
                    rrdset_done(m->st_inodes);

                    rendered++;
                }

                if (likely(rendered))
                    m->collected++;
            }
        }
    } else {
        error("DISABLED: getmntinfo module");
        return 1;
    }

    mount_points_cleanup();

    return 0;
}