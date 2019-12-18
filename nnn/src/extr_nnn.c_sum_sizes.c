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
struct stat {scalar_t__ st_size; } ;
struct FTW {int dummy; } ;

/* Variables and functions */
 int FTW_D ; 
 int FTW_F ; 
 int /*<<< orphan*/  ent_blocks ; 
 int /*<<< orphan*/  num_files ; 

__attribute__((used)) static int sum_sizes(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
	(void) fpath;
	(void) ftwbuf;

	if (sb->st_size && (typeflag == FTW_F || typeflag == FTW_D))
		ent_blocks += sb->st_size;

	++num_files;
	return 0;
}