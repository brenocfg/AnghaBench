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
struct stat {int dummy; } ;

/* Variables and functions */
 int FTW_F ; 
 int /*<<< orphan*/  unlink (char const*) ; 

__attribute__((used)) static int unlink_cb(const char *fpath, const struct stat *sb, int typeflag)
{
    if (typeflag == FTW_F){
        unlink(fpath);
    }
    return 0;
}