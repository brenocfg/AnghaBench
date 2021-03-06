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
struct stat {int /*<<< orphan*/  st_size; } ;
struct csys_block {int /*<<< orphan*/  file_size; int /*<<< orphan*/ * file_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERRS (char*,int /*<<< orphan*/ *) ; 
 int ERR_FATAL ; 
 int stat (int /*<<< orphan*/ *,struct stat*) ; 

int
block_stat_file(struct csys_block *block)
{
	struct stat st;
	int err;

	if (block->file_name == NULL)
		return 0;

	err = stat(block->file_name, &st);
	if (err){
		ERRS("stat failed on %s", block->file_name);
		return ERR_FATAL;
	}

	block->file_size = st.st_size;
	return 0;
}