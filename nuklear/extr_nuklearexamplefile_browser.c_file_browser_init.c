#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct media {int dummy; } ;
struct file_browser {char* home; char* directory; char* desktop; int /*<<< orphan*/  dir_count; void* directories; int /*<<< orphan*/  file_count; void* files; struct media* media; } ;
struct TYPE_2__ {char* pw_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_PATH_LEN ; 
 void* dir_list (char*,int,int /*<<< orphan*/ *) ; 
 char* getenv (char*) ; 
 TYPE_1__* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/  memset (struct file_browser*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
file_browser_init(struct file_browser *browser, struct media *media)
{
    memset(browser, 0, sizeof(*browser));
    browser->media = media;
    {
        /* load files and sub-directory list */
        const char *home = getenv("HOME");
#ifdef _WIN32
        if (!home) home = getenv("USERPROFILE");
#else
        if (!home) home = getpwuid(getuid())->pw_dir;
        {
            size_t l;
            strncpy(browser->home, home, MAX_PATH_LEN);
            l = strlen(browser->home);
            strcpy(browser->home + l, "/");
            strcpy(browser->directory, browser->home);
        }
#endif
        {
            size_t l;
            strcpy(browser->desktop, browser->home);
            l = strlen(browser->desktop);
            strcpy(browser->desktop + l, "desktop/");
        }
        browser->files = dir_list(browser->directory, 0, &browser->file_count);
        browser->directories = dir_list(browser->directory, 1, &browser->dir_count);
    }
}