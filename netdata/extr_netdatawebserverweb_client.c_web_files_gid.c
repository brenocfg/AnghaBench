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
struct group {char* gr_name; int /*<<< orphan*/  gr_gid; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SECTION_WEB ; 
 int /*<<< orphan*/  D_WEB_CLIENT ; 
 char* config_get (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  getegid () ; 
 struct group* getgrgid (int /*<<< orphan*/ ) ; 
 struct group* getgrnam (char*) ; 
 scalar_t__ unlikely (int) ; 

gid_t web_files_gid(void) {
    static char *web_group = NULL;
    static gid_t owner_gid = 0;

    if(unlikely(!web_group)) {
        // getgrgid() is not thread safe,
        // but we have called this function once
        // while single threaded
        struct group *gr = getgrgid(getegid());
        web_group = config_get(CONFIG_SECTION_WEB, "web files group", (gr)?(gr->gr_name?gr->gr_name:""):"");
        if(!web_group || !*web_group)
            owner_gid = getegid();
        else {
            // getgrnam() is not thread safe,
            // but we have called this function once
            // while single threaded
            gr = getgrnam(web_group);
            if(!gr) {
                error("Group '%s' is not present. Ignoring option.", web_group);
                owner_gid = getegid();
            }
            else {
                debug(D_WEB_CLIENT, "Web files group set to %s.", web_group);
                owner_gid = gr->gr_gid;
            }
        }
    }

    return(owner_gid);
}