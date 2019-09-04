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
typedef  int /*<<< orphan*/  uid_t ;
struct passwd {char* pw_name; int /*<<< orphan*/  pw_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SECTION_WEB ; 
 int /*<<< orphan*/  D_WEB_CLIENT ; 
 char* config_get (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  geteuid () ; 
 struct passwd* getpwnam (char*) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

uid_t web_files_uid(void) {
    static char *web_owner = NULL;
    static uid_t owner_uid = 0;

    if(unlikely(!web_owner)) {
        // getpwuid() is not thread safe,
        // but we have called this function once
        // while single threaded
        struct passwd *pw = getpwuid(geteuid());
        web_owner = config_get(CONFIG_SECTION_WEB, "web files owner", (pw)?(pw->pw_name?pw->pw_name:""):"");
        if(!web_owner || !*web_owner)
            owner_uid = geteuid();
        else {
            // getpwnam() is not thread safe,
            // but we have called this function once
            // while single threaded
            pw = getpwnam(web_owner);
            if(!pw) {
                error("User '%s' is not present. Ignoring option.", web_owner);
                owner_uid = geteuid();
            }
            else {
                debug(D_WEB_CLIENT, "Web files owner set to %s.", web_owner);
                owner_uid = pw->pw_uid;
            }
        }
    }

    return(owner_uid);
}