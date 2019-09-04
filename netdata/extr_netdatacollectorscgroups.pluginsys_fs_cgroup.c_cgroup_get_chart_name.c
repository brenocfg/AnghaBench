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
struct cgroup {int pending_renames; int /*<<< orphan*/  chart_id; int /*<<< orphan*/  hash_chart; int /*<<< orphan*/  chart_title; scalar_t__ enabled; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CGROUP_CHARTID_LINE_MAX ; 
 int /*<<< orphan*/  D_CGROUP ; 
 int /*<<< orphan*/  cgroup_chart_id_strdupz (char*) ; 
 int /*<<< orphan*/  cgroup_title_strdupz (char*) ; 
 int /*<<< orphan*/  cgroups_rename_script ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 char* fgets (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freez (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int mypclose (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mypopen (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* trim (char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void cgroup_get_chart_name(struct cgroup *cg) {
    debug(D_CGROUP, "looking for the name of cgroup '%s' with chart id '%s' and title '%s'", cg->id, cg->chart_id, cg->chart_title);

    pid_t cgroup_pid;
    char command[CGROUP_CHARTID_LINE_MAX + 1];

    snprintfz(command, CGROUP_CHARTID_LINE_MAX, "exec %s '%s'", cgroups_rename_script, cg->chart_id);

    debug(D_CGROUP, "executing command \"%s\" for cgroup '%s'", command, cg->chart_id);
    FILE *fp = mypopen(command, &cgroup_pid);
    if(fp) {
        // debug(D_CGROUP, "reading from command '%s' for cgroup '%s'", command, cg->id);
        char buffer[CGROUP_CHARTID_LINE_MAX + 1];
        char *s = fgets(buffer, CGROUP_CHARTID_LINE_MAX, fp);
        // debug(D_CGROUP, "closing command for cgroup '%s'", cg->id);
        int name_error = mypclose(fp, cgroup_pid);
        // debug(D_CGROUP, "closed command for cgroup '%s'", cg->id);

        if(s && *s && *s != '\n') {
            debug(D_CGROUP, "cgroup '%s' should be renamed to '%s'", cg->chart_id, s);

            s = trim(s);
            if (s) {
                if(likely(name_error==0))
                    cg->pending_renames = 0;
                else if (unlikely(name_error==3)) {
                    debug(D_CGROUP, "cgroup '%s' disabled based due to rename command output", cg->chart_id);
                    cg->enabled = 0;
                }

                if(likely(cg->pending_renames < 2)) {
                    freez(cg->chart_title);
                    cg->chart_title = cgroup_title_strdupz(s);

                    freez(cg->chart_id);
                    cg->chart_id = cgroup_chart_id_strdupz(s);
                    cg->hash_chart = simple_hash(cg->chart_id);
                }
            }
        }
    }
    else
        error("CGROUP: cannot popen(\"%s\", \"r\").", command);
}