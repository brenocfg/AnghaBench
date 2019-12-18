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

/* Variables and functions */
 int errno ; 
 int /*<<< orphan*/  ftw (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ rmdir (char*) ; 
 int /*<<< orphan*/  unlink_cb ; 

__attribute__((used)) static void rmrfdir(char *path)
{
    ftw(path, unlink_cb, 16);
    if (rmdir(path) != 0) {
        printf("failed rmdir, errno=%d\n", errno);
    }
}