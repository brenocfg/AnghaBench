#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_10__ {int h_err; TYPE_2__* h_transaction; } ;
typedef  TYPE_3__ handle_t ;
struct TYPE_9__ {TYPE_1__* t_journal; } ;
struct TYPE_8__ {struct super_block* j_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ext4_std_error (struct super_block*,char const*,unsigned int,int) ; 
 int /*<<< orphan*/  ext4_handle_valid (TYPE_3__*) ; 
 int /*<<< orphan*/  ext4_put_nojournal (TYPE_3__*) ; 
 int jbd2_journal_stop (TYPE_3__*) ; 

int __ext4_journal_stop(const char *where, unsigned int line, handle_t *handle)
{
	struct super_block *sb;
	int err;
	int rc;

	if (!ext4_handle_valid(handle)) {
		ext4_put_nojournal(handle);
		return 0;
	}

	err = handle->h_err;
	if (!handle->h_transaction) {
		rc = jbd2_journal_stop(handle);
		return err ? err : rc;
	}

	sb = handle->h_transaction->t_journal->j_private;
	rc = jbd2_journal_stop(handle);

	if (!err)
		err = rc;
	if (err)
		__ext4_std_error(sb, where, line, err);
	return err;
}