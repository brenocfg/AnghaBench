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
struct rseq {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  RSEQ_FLAG_UNREGISTER ; 
 int /*<<< orphan*/  RSEQ_SIG ; 
 int /*<<< orphan*/  __rseq_abi ; 
 scalar_t__ refcount ; 
 int /*<<< orphan*/  signal_off_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_restore (int /*<<< orphan*/ ) ; 
 int sys_rseq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rseq_unregister_current_thread(void)
{
	int rc, ret = 0;
	sigset_t oldset;

	signal_off_save(&oldset);
	if (--refcount)
		goto end;
	rc = sys_rseq(&__rseq_abi, sizeof(struct rseq),
		      RSEQ_FLAG_UNREGISTER, RSEQ_SIG);
	if (!rc)
		goto end;
	ret = -1;
end:
	signal_restore(oldset);
	return ret;
}