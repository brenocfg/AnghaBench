#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rseq {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_3__ {int /*<<< orphan*/  cpu_id; } ;

/* Variables and functions */
 scalar_t__ EBUSY ; 
 int /*<<< orphan*/  RSEQ_CPU_ID_REGISTRATION_FAILED ; 
 int /*<<< orphan*/  RSEQ_SIG ; 
 scalar_t__ UINT_MAX ; 
 TYPE_1__ __rseq_abi ; 
 scalar_t__ __rseq_refcount ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 scalar_t__ rseq_current_cpu_raw () ; 
 int /*<<< orphan*/  rseq_ownership ; 
 int /*<<< orphan*/  signal_off_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_restore (int /*<<< orphan*/ ) ; 
 int sys_rseq (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rseq_register_current_thread(void)
{
	int rc, ret = 0;
	sigset_t oldset;

	if (!rseq_ownership)
		return 0;
	signal_off_save(&oldset);
	if (__rseq_refcount == UINT_MAX) {
		ret = -1;
		goto end;
	}
	if (__rseq_refcount++)
		goto end;
	rc = sys_rseq(&__rseq_abi, sizeof(struct rseq), 0, RSEQ_SIG);
	if (!rc) {
		assert(rseq_current_cpu_raw() >= 0);
		goto end;
	}
	if (errno != EBUSY)
		__rseq_abi.cpu_id = RSEQ_CPU_ID_REGISTRATION_FAILED;
	ret = -1;
	__rseq_refcount--;
end:
	signal_restore(oldset);
	return ret;
}