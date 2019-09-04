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
struct file_browser {int /*<<< orphan*/  dir_count; void* directories; int /*<<< orphan*/  file_count; void* files; int /*<<< orphan*/  directory; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_PATH_LEN ; 
 int /*<<< orphan*/  dir_free_list (void*,int /*<<< orphan*/ ) ; 
 void* dir_list (char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
file_browser_reload_directory_content(struct file_browser *browser, const char *path)
{
    strncpy(browser->directory, path, MAX_PATH_LEN);
    dir_free_list(browser->files, browser->file_count);
    dir_free_list(browser->directories, browser->dir_count);
    browser->files = dir_list(path, 0, &browser->file_count);
    browser->directories = dir_list(path, 1, &browser->dir_count);
}