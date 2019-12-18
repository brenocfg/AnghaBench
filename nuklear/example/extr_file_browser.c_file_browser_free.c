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
struct file_browser {int /*<<< orphan*/ * directories; int /*<<< orphan*/ * files; int /*<<< orphan*/  dir_count; int /*<<< orphan*/  file_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  dir_free_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct file_browser*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
file_browser_free(struct file_browser *browser)
{
    if (browser->files)
        dir_free_list(browser->files, browser->file_count);
    if (browser->directories)
        dir_free_list(browser->directories, browser->dir_count);
    browser->files = NULL;
    browser->directories = NULL;
    memset(browser, 0, sizeof(*browser));
}