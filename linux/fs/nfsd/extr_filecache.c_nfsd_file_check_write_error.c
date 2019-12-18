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
struct nfsd_file {struct file* nf_file; } ;
struct file {int f_mode; int /*<<< orphan*/  f_wb_err; int /*<<< orphan*/  f_mapping; } ;

/* Variables and functions */
 int FMODE_WRITE ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int filemap_check_wb_err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfsd_file_check_write_error(struct nfsd_file *nf)
{
	struct file *file = nf->nf_file;

	if (!file || !(file->f_mode & FMODE_WRITE))
		return 0;
	return filemap_check_wb_err(file->f_mapping, READ_ONCE(file->f_wb_err));
}