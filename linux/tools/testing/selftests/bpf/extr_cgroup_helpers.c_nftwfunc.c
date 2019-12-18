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
struct FTW {int dummy; } ;

/* Variables and functions */
 int FTW_D ; 
 int /*<<< orphan*/  log_err (char*,char const*) ; 
 scalar_t__ rmdir (char const*) ; 

__attribute__((used)) static int nftwfunc(const char *filename, const struct stat *statptr,
		    int fileflags, struct FTW *pfwt)
{
	if ((fileflags & FTW_D) && rmdir(filename))
		log_err("Removing cgroup: %s", filename);
	return 0;
}