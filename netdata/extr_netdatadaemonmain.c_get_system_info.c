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
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  R_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freez (char*) ; 
 int /*<<< orphan*/  info (char*,char*,...) ; 
 char* mallocz (int) ; 
 int /*<<< orphan*/  mypclose (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mypopen (char*,int /*<<< orphan*/ *) ; 
 char* netdata_configured_primary_plugins_dir ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ unlikely (int) ; 

int get_system_info () {
    char *script;
    script = mallocz(sizeof(char) * (strlen(netdata_configured_primary_plugins_dir) + strlen("system-info.sh") + 2));
    sprintf(script, "%s/%s", netdata_configured_primary_plugins_dir, "system-info.sh");
    if (unlikely(access(script, R_OK) != 0)) {
        info("System info script %s not found.",script);
        freez(script);
        return 1;
    }

    pid_t command_pid;

    info("Executing %s", script);

    FILE *fp = mypopen(script, &command_pid);
    if(fp) {
        char buffer[200 + 1];
        while (fgets(buffer, 200, fp) != NULL) {
            char *name=buffer;
            char *value=buffer;
            while (*value && *value != '=') value++;
            if (*value=='=') {
                *value='\0';
                value++;
                char *newline = value + strlen(value) - 1;
                (*newline)='\0';
            }
            if (name && value && *name && *value) {
                info("%s=%s", name, value);
                setenv(name, value, 1);
            }
        }
        mypclose(fp, command_pid);
    }
    freez(script);
    return 0;
}