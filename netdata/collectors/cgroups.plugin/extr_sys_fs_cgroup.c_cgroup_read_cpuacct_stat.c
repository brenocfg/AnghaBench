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
typedef  scalar_t__ uint32_t ;
struct cpuacct_stat {int updated; scalar_t__ enabled; void* system; void* user; int /*<<< orphan*/  filename; } ;
typedef  int /*<<< orphan*/  procfile ;

/* Variables and functions */
 scalar_t__ CONFIG_BOOLEAN_AUTO ; 
 scalar_t__ CONFIG_BOOLEAN_YES ; 
 int /*<<< orphan*/  PROCFILE_FLAG_DEFAULT ; 
 int cgroups_check ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 scalar_t__ netdata_zero_metrics_enabled ; 
 unsigned long procfile_lines (int /*<<< orphan*/ *) ; 
 char* procfile_lineword (int /*<<< orphan*/ *,unsigned long,int) ; 
 int /*<<< orphan*/ * procfile_readall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * procfile_reopen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ simple_hash (char*) ; 
 void* str2ull (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 scalar_t__ system_hash ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ user_hash ; 

__attribute__((used)) static inline void cgroup_read_cpuacct_stat(struct cpuacct_stat *cp) {
    static procfile *ff = NULL;

    if(likely(cp->filename)) {
        ff = procfile_reopen(ff, cp->filename, NULL, PROCFILE_FLAG_DEFAULT);
        if(unlikely(!ff)) {
            cp->updated = 0;
            cgroups_check = 1;
            return;
        }

        ff = procfile_readall(ff);
        if(unlikely(!ff)) {
            cp->updated = 0;
            cgroups_check = 1;
            return;
        }

        unsigned long i, lines = procfile_lines(ff);

        if(unlikely(lines < 1)) {
            error("CGROUP: file '%s' should have 1+ lines.", cp->filename);
            cp->updated = 0;
            return;
        }

        for(i = 0; i < lines ; i++) {
            char *s = procfile_lineword(ff, i, 0);
            uint32_t hash = simple_hash(s);

            if(unlikely(hash == user_hash && !strcmp(s, "user")))
                cp->user = str2ull(procfile_lineword(ff, i, 1));

            else if(unlikely(hash == system_hash && !strcmp(s, "system")))
                cp->system = str2ull(procfile_lineword(ff, i, 1));
        }

        cp->updated = 1;

        if(unlikely(cp->enabled == CONFIG_BOOLEAN_AUTO &&
                    (cp->user || cp->system || netdata_zero_metrics_enabled == CONFIG_BOOLEAN_YES)))
            cp->enabled = CONFIG_BOOLEAN_YES;
    }
}