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
struct journal_head {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int do_get_write_access (int /*<<< orphan*/ *,struct journal_head*,int /*<<< orphan*/ ) ; 
 struct journal_head* jbd2_journal_add_journal_head (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd2_journal_put_journal_head (struct journal_head*) ; 
 scalar_t__ jbd2_write_access_granted (int /*<<< orphan*/ *,struct buffer_head*,int) ; 

int jbd2_journal_get_write_access(handle_t *handle, struct buffer_head *bh)
{
	struct journal_head *jh;
	int rc;

	if (jbd2_write_access_granted(handle, bh, false))
		return 0;

	jh = jbd2_journal_add_journal_head(bh);
	/* We do not want to get caught playing with fields which the
	 * log thread also manipulates.  Make sure that the buffer
	 * completes any outstanding IO before proceeding. */
	rc = do_get_write_access(handle, jh, 0);
	jbd2_journal_put_journal_head(jh);
	return rc;
}