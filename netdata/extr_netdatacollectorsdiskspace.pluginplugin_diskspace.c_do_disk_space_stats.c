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
struct statvfs {unsigned long f_frsize; unsigned long f_bsize; scalar_t__ f_bavail; scalar_t__ f_blocks; scalar_t__ f_bfree; scalar_t__ f_favail; scalar_t__ f_files; scalar_t__ f_ffree; } ;
struct stat {int st_mode; } ;
struct mountinfo {char* mount_point; char* persistent_id; char* filesystem; char* root; int flags; int /*<<< orphan*/  mount_source; } ;
struct mount_point_metadata {int do_space; int do_inodes; int shown_error; int updated; int /*<<< orphan*/  collected; int /*<<< orphan*/ * st_inodes; int /*<<< orphan*/ * rd_inodes_reserved; int /*<<< orphan*/ * rd_inodes_used; int /*<<< orphan*/ * rd_inodes_avail; int /*<<< orphan*/ * st_space; int /*<<< orphan*/ * rd_space_reserved; int /*<<< orphan*/ * rd_space_used; int /*<<< orphan*/ * rd_space_avail; } ;
typedef  scalar_t__ fsfilcnt_t ;
typedef  scalar_t__ fsblkcnt_t ;
typedef  int collected_number ;
typedef  int /*<<< orphan*/  SIMPLE_PREFIX_MODE ;
typedef  int /*<<< orphan*/  SIMPLE_PATTERN ;

/* Variables and functions */
 int CONFIG_BOOLEAN_AUTO ; 
 int CONFIG_BOOLEAN_NO ; 
 void* CONFIG_BOOLEAN_YES ; 
 char* CONFIG_SECTION_DISKSPACE ; 
 int /*<<< orphan*/  DEFAULT_EXCLUDED_FILESYSTEMS ; 
 int /*<<< orphan*/  DELAULT_EXCLUDED_PATHS ; 
 int /*<<< orphan*/  DICTIONARY_FLAG_SINGLE_THREADED ; 
 int MOUNTINFO_READONLY ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_DISKSPACE_INODES ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_DISKSPACE_SPACE ; 
 int /*<<< orphan*/  PLUGIN_DISKSPACE_NAME ; 
 int /*<<< orphan*/  RRDSET_TYPE_STACKED ; 
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 int /*<<< orphan*/  SIMPLE_PATTERN_EXACT ; 
 int /*<<< orphan*/  SIMPLE_PATTERN_PREFIX ; 
 int S_IFDIR ; 
 int S_IFMT ; 
 int /*<<< orphan*/  config_get (char*,char*,int /*<<< orphan*/ ) ; 
 int config_get_boolean_ondemand (char*,char*,int) ; 
 int config_move (char*,char*,char*,char*) ; 
 scalar_t__ dict_mountpoints ; 
 scalar_t__ dictionary_create (int /*<<< orphan*/ ) ; 
 struct mount_point_metadata* dictionary_get (scalar_t__,char*) ; 
 struct mount_point_metadata* dictionary_set (scalar_t__,char*,struct mount_point_metadata*,int) ; 
 int /*<<< orphan*/  error (char*,char*,char const*,char*,char*) ; 
 scalar_t__ likely (int) ; 
 void* rrddim_add (int /*<<< orphan*/ *,char*,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* rrdset_create_localhost (char*,char const*,int /*<<< orphan*/ *,char const*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 void* rrdset_find_bytype_localhost (char*,char const*) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * simple_pattern_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int simple_pattern_matches (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snprintfz (char*,int,char*,char const*,...) ; 
 int stat (char*,struct stat*) ; 
 scalar_t__ statvfs (char*,struct statvfs*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void do_disk_space_stats(struct mountinfo *mi, int update_every) {
    const char *family = mi->mount_point;
    const char *disk = mi->persistent_id;

    static SIMPLE_PATTERN *excluded_mountpoints = NULL;
    static SIMPLE_PATTERN *excluded_filesystems = NULL;
    int do_space, do_inodes;

    if(unlikely(!dict_mountpoints)) {
        SIMPLE_PREFIX_MODE mode = SIMPLE_PATTERN_EXACT;

        if(config_move("plugin:proc:/proc/diskstats", "exclude space metrics on paths", CONFIG_SECTION_DISKSPACE, "exclude space metrics on paths") != -1) {
            // old configuration, enable backwards compatibility
            mode = SIMPLE_PATTERN_PREFIX;
        }

        excluded_mountpoints = simple_pattern_create(
                config_get(CONFIG_SECTION_DISKSPACE, "exclude space metrics on paths", DELAULT_EXCLUDED_PATHS)
                , NULL
                , mode
        );

        excluded_filesystems = simple_pattern_create(
                config_get(CONFIG_SECTION_DISKSPACE, "exclude space metrics on filesystems", DEFAULT_EXCLUDED_FILESYSTEMS)
                , NULL
                , SIMPLE_PATTERN_EXACT
        );

        dict_mountpoints = dictionary_create(DICTIONARY_FLAG_SINGLE_THREADED);
    }

    struct mount_point_metadata *m = dictionary_get(dict_mountpoints, mi->mount_point);
    if(unlikely(!m)) {
        char var_name[4096 + 1];
        snprintfz(var_name, 4096, "plugin:proc:diskspace:%s", mi->mount_point);

        int def_space = config_get_boolean_ondemand(CONFIG_SECTION_DISKSPACE, "space usage for all disks", CONFIG_BOOLEAN_AUTO);
        int def_inodes = config_get_boolean_ondemand(CONFIG_SECTION_DISKSPACE, "inodes usage for all disks", CONFIG_BOOLEAN_AUTO);

        if(unlikely(simple_pattern_matches(excluded_mountpoints, mi->mount_point))) {
            def_space = CONFIG_BOOLEAN_NO;
            def_inodes = CONFIG_BOOLEAN_NO;
        }

        if(unlikely(simple_pattern_matches(excluded_filesystems, mi->filesystem))) {
            def_space = CONFIG_BOOLEAN_NO;
            def_inodes = CONFIG_BOOLEAN_NO;
        }

        // check if the mount point is a directory #2407
        // but only when it is enabled by default #4491
        if(def_space != CONFIG_BOOLEAN_NO || def_inodes != CONFIG_BOOLEAN_NO) {
            struct stat bs;
            if(stat(mi->mount_point, &bs) == -1) {
                error("DISKSPACE: Cannot stat() mount point '%s' (disk '%s', filesystem '%s', root '%s')."
                      , mi->mount_point
                      , disk
                      , mi->filesystem?mi->filesystem:""
                      , mi->root?mi->root:""
                );
                def_space = CONFIG_BOOLEAN_NO;
                def_inodes = CONFIG_BOOLEAN_NO;
            }
            else {
                if((bs.st_mode & S_IFMT) != S_IFDIR) {
                    error("DISKSPACE: Mount point '%s' (disk '%s', filesystem '%s', root '%s') is not a directory."
                          , mi->mount_point
                          , disk
                          , mi->filesystem?mi->filesystem:""
                          , mi->root?mi->root:""
                    );
                    def_space = CONFIG_BOOLEAN_NO;
                    def_inodes = CONFIG_BOOLEAN_NO;
                }
            }
        }

        do_space = config_get_boolean_ondemand(var_name, "space usage", def_space);
        do_inodes = config_get_boolean_ondemand(var_name, "inodes usage", def_inodes);

        struct mount_point_metadata mp = {
                .do_space = do_space,
                .do_inodes = do_inodes,
                .shown_error = 0,
                .updated = 0,

                .collected = 0,

                .st_space = NULL,
                .rd_space_avail = NULL,
                .rd_space_used = NULL,
                .rd_space_reserved = NULL,

                .st_inodes = NULL,
                .rd_inodes_avail = NULL,
                .rd_inodes_used = NULL,
                .rd_inodes_reserved = NULL
        };

        m = dictionary_set(dict_mountpoints, mi->mount_point, &mp, sizeof(struct mount_point_metadata));
    }

    m->updated = 1;

    if(unlikely(m->do_space == CONFIG_BOOLEAN_NO && m->do_inodes == CONFIG_BOOLEAN_NO))
        return;

    if(unlikely(mi->flags & MOUNTINFO_READONLY && !m->collected && m->do_space != CONFIG_BOOLEAN_YES && m->do_inodes != CONFIG_BOOLEAN_YES))
        return;

    struct statvfs buff_statvfs;
    if (statvfs(mi->mount_point, &buff_statvfs) < 0) {
        if(!m->shown_error) {
            error("DISKSPACE: failed to statvfs() mount point '%s' (disk '%s', filesystem '%s', root '%s')"
                  , mi->mount_point
                  , disk
                  , mi->filesystem?mi->filesystem:""
                  , mi->root?mi->root:""
            );
            m->shown_error = 1;
        }
        return;
    }
    m->shown_error = 0;

    // logic found at get_fs_usage() in coreutils
    unsigned long bsize = (buff_statvfs.f_frsize) ? buff_statvfs.f_frsize : buff_statvfs.f_bsize;

    fsblkcnt_t bavail         = buff_statvfs.f_bavail;
    fsblkcnt_t btotal         = buff_statvfs.f_blocks;
    fsblkcnt_t bavail_root    = buff_statvfs.f_bfree;
    fsblkcnt_t breserved_root = bavail_root - bavail;
    fsblkcnt_t bused;
    if(likely(btotal >= bavail_root))
        bused = btotal - bavail_root;
    else
        bused = bavail_root - btotal;

#ifdef NETDATA_INTERNAL_CHECKS
    if(unlikely(btotal != bavail + breserved_root + bused))
        error("DISKSPACE: disk block statistics for '%s' (disk '%s') do not sum up: total = %llu, available = %llu, reserved = %llu, used = %llu", mi->mount_point, disk, (unsigned long long)btotal, (unsigned long long)bavail, (unsigned long long)breserved_root, (unsigned long long)bused);
#endif

    // --------------------------------------------------------------------------

    fsfilcnt_t favail         = buff_statvfs.f_favail;
    fsfilcnt_t ftotal         = buff_statvfs.f_files;
    fsfilcnt_t favail_root    = buff_statvfs.f_ffree;
    fsfilcnt_t freserved_root = favail_root - favail;
    fsfilcnt_t fused          = ftotal - favail_root;

    if(m->do_inodes == CONFIG_BOOLEAN_AUTO && favail == (fsfilcnt_t)-1) {
        // this file system does not support inodes reporting
        // eg. cephfs
        m->do_inodes = CONFIG_BOOLEAN_NO;
    }

#ifdef NETDATA_INTERNAL_CHECKS
    if(unlikely(btotal != bavail + breserved_root + bused))
        error("DISKSPACE: disk inode statistics for '%s' (disk '%s') do not sum up: total = %llu, available = %llu, reserved = %llu, used = %llu", mi->mount_point, disk, (unsigned long long)ftotal, (unsigned long long)favail, (unsigned long long)freserved_root, (unsigned long long)fused);
#endif

    // --------------------------------------------------------------------------

    int rendered = 0;

    if(m->do_space == CONFIG_BOOLEAN_YES || (m->do_space == CONFIG_BOOLEAN_AUTO && (bavail || breserved_root || bused))) {
        if(unlikely(!m->st_space)) {
            m->do_space = CONFIG_BOOLEAN_YES;
            m->st_space = rrdset_find_bytype_localhost("disk_space", disk);
            if(unlikely(!m->st_space)) {
                char title[4096 + 1];
                snprintfz(title, 4096, "Disk Space Usage for %s [%s]", family, mi->mount_source);
                m->st_space = rrdset_create_localhost(
                        "disk_space"
                        , disk
                        , NULL
                        , family
                        , "disk.space"
                        , title
                        , "GiB"
                        , PLUGIN_DISKSPACE_NAME
                        , NULL
                        , NETDATA_CHART_PRIO_DISKSPACE_SPACE
                        , update_every
                        , RRDSET_TYPE_STACKED
                );
            }

            m->rd_space_avail    = rrddim_add(m->st_space, "avail", NULL, (collected_number)bsize, 1024 * 1024 * 1024, RRD_ALGORITHM_ABSOLUTE);
            m->rd_space_used     = rrddim_add(m->st_space, "used", NULL, (collected_number)bsize, 1024 * 1024 * 1024, RRD_ALGORITHM_ABSOLUTE);
            m->rd_space_reserved = rrddim_add(m->st_space, "reserved_for_root", "reserved for root", (collected_number)bsize, 1024 * 1024 * 1024, RRD_ALGORITHM_ABSOLUTE);
        }
        else
            rrdset_next(m->st_space);

        rrddim_set_by_pointer(m->st_space, m->rd_space_avail,    (collected_number)bavail);
        rrddim_set_by_pointer(m->st_space, m->rd_space_used,     (collected_number)bused);
        rrddim_set_by_pointer(m->st_space, m->rd_space_reserved, (collected_number)breserved_root);
        rrdset_done(m->st_space);

        rendered++;
    }

    // --------------------------------------------------------------------------

    if(m->do_inodes == CONFIG_BOOLEAN_YES || (m->do_inodes == CONFIG_BOOLEAN_AUTO && (favail || freserved_root || fused))) {
        if(unlikely(!m->st_inodes)) {
            m->do_inodes = CONFIG_BOOLEAN_YES;
            m->st_inodes = rrdset_find_bytype_localhost("disk_inodes", disk);
            if(unlikely(!m->st_inodes)) {
                char title[4096 + 1];
                snprintfz(title, 4096, "Disk Files (inodes) Usage for %s [%s]", family, mi->mount_source);
                m->st_inodes = rrdset_create_localhost(
                        "disk_inodes"
                        , disk
                        , NULL
                        , family
                        , "disk.inodes"
                        , title
                        , "inodes"
                        , PLUGIN_DISKSPACE_NAME
                        , NULL
                        , NETDATA_CHART_PRIO_DISKSPACE_INODES
                        , update_every
                        , RRDSET_TYPE_STACKED
                );
            }

            m->rd_inodes_avail    = rrddim_add(m->st_inodes, "avail", NULL, 1, 1, RRD_ALGORITHM_ABSOLUTE);
            m->rd_inodes_used     = rrddim_add(m->st_inodes, "used", NULL, 1, 1, RRD_ALGORITHM_ABSOLUTE);
            m->rd_inodes_reserved = rrddim_add(m->st_inodes, "reserved_for_root", "reserved for root", 1, 1, RRD_ALGORITHM_ABSOLUTE);
        }
        else
            rrdset_next(m->st_inodes);

        rrddim_set_by_pointer(m->st_inodes, m->rd_inodes_avail,    (collected_number)favail);
        rrddim_set_by_pointer(m->st_inodes, m->rd_inodes_used,     (collected_number)fused);
        rrddim_set_by_pointer(m->st_inodes, m->rd_inodes_reserved, (collected_number)freserved_root);
        rrdset_done(m->st_inodes);

        rendered++;
    }

    // --------------------------------------------------------------------------

    if(likely(rendered))
        m->collected++;
}