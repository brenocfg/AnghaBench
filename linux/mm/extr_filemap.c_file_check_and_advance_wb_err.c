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
struct file {int /*<<< orphan*/  f_lock; int /*<<< orphan*/  f_wb_err; struct address_space* f_mapping; } ;
struct address_space {int /*<<< orphan*/  flags; int /*<<< orphan*/  wb_err; } ;
typedef  int /*<<< orphan*/  errseq_t ;

/* Variables and functions */
 int /*<<< orphan*/  AS_EIO ; 
 int /*<<< orphan*/  AS_ENOSPC ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ errseq_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int errseq_check_and_advance (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_file_check_and_advance_wb_err (struct file*,int /*<<< orphan*/ ) ; 

int file_check_and_advance_wb_err(struct file *file)
{
	int err = 0;
	errseq_t old = READ_ONCE(file->f_wb_err);
	struct address_space *mapping = file->f_mapping;

	/* Locklessly handle the common case where nothing has changed */
	if (errseq_check(&mapping->wb_err, old)) {
		/* Something changed, must use slow path */
		spin_lock(&file->f_lock);
		old = file->f_wb_err;
		err = errseq_check_and_advance(&mapping->wb_err,
						&file->f_wb_err);
		trace_file_check_and_advance_wb_err(file, old);
		spin_unlock(&file->f_lock);
	}

	/*
	 * We're mostly using this function as a drop in replacement for
	 * filemap_check_errors. Clear AS_EIO/AS_ENOSPC to emulate the effect
	 * that the legacy code would have had on these flags.
	 */
	clear_bit(AS_EIO, &mapping->flags);
	clear_bit(AS_ENOSPC, &mapping->flags);
	return err;
}