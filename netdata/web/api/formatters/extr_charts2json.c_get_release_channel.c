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
typedef  int /*<<< orphan*/  procfile ;

/* Variables and functions */
 int /*<<< orphan*/  FILENAME_MAX ; 
 int /*<<< orphan*/  PROCFILE_FLAG_DEFAULT ; 
 int /*<<< orphan*/  netdata_configured_user_config_dir ; 
 int /*<<< orphan*/  procfile_close (int /*<<< orphan*/ *) ; 
 unsigned int procfile_lines (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  procfile_lineword (int /*<<< orphan*/ *,unsigned int,int) ; 
 int /*<<< orphan*/  procfile_linewords (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/ * procfile_open (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * procfile_readall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  procfile_set_quotes (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline const char* get_release_channel() {
    static int use_stable = -1;

    if (use_stable == -1) {
		char filename[FILENAME_MAX + 1];
        snprintfz(filename, FILENAME_MAX, "%s/.environment", netdata_configured_user_config_dir);
        procfile *ff = procfile_open(filename, "=", PROCFILE_FLAG_DEFAULT);
        if(!ff) {
            use_stable=1;
        } else {
            procfile_set_quotes(ff, "'\"");
            ff = procfile_readall(ff);
            if(!ff) {
                use_stable=1;
            } else {
                unsigned int i;
                for(i = 0; i < procfile_lines(ff); i++) {
                    if (!procfile_linewords(ff, i)) continue;

                    if (!strcmp(procfile_lineword(ff, i, 0), "RELEASE_CHANNEL") && !strcmp(procfile_lineword(ff, i, 1), "stable")) {
                        use_stable = 1;
                        break;
                    }
                }
                procfile_close(ff);
                if (use_stable == -1) use_stable = 0;
            }
        }
    }
    return (use_stable)?"stable":"nightly";
}