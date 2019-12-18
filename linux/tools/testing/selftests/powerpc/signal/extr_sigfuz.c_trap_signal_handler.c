#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int* gp_regs; } ;
struct TYPE_12__ {TYPE_4__* uc_link; TYPE_1__ uc_mcontext; } ;
typedef  TYPE_3__ ucontext_t ;
typedef  int /*<<< orphan*/  siginfo_t ;
struct TYPE_11__ {int* gp_regs; } ;
struct TYPE_13__ {TYPE_2__ uc_mcontext; } ;

/* Variables and functions */
 int ARG_MESS_WITH_MSR_AT ; 
 int ARG_MESS_WITH_TM_BEFORE ; 
 int /*<<< orphan*/  MADV_DONTNEED ; 
 int MSR_TS_S ; 
 int MSR_TS_T ; 
 size_t PT_CCR ; 
 size_t PT_CTR ; 
 size_t PT_DAR ; 
 size_t PT_DSCR ; 
 size_t PT_DSISR ; 
 size_t PT_LNK ; 
 size_t PT_MSR ; 
 size_t PT_NIP ; 
 size_t PT_ORIG_R3 ; 
 size_t PT_REGS_COUNT ; 
 size_t PT_RESULT ; 
 size_t PT_SOFTE ; 
 size_t PT_TRAP ; 
 size_t PT_XER ; 
 int args ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  madvise (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 TYPE_4__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,void*,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mess_with_tm () ; 
 scalar_t__ one_in_chance (int) ; 
 int /*<<< orphan*/  rand () ; 
 void* random () ; 
 TYPE_4__* tmp_uc ; 

__attribute__((used)) static void trap_signal_handler(int signo, siginfo_t *si, void *uc)
{
	ucontext_t *ucp = uc;

	ucp->uc_link = tmp_uc;

	/*
	 * Set uc_link in three possible ways:
	 *  - Setting a single 'int' in the whole chunk
	 *  - Cloning ucp into uc_link
	 *  - Allocating a new memory chunk
	 */
	if (one_in_chance(3)) {
		memset(ucp->uc_link, rand(), sizeof(ucontext_t));
	} else if (one_in_chance(2)) {
		memcpy(ucp->uc_link, uc, sizeof(ucontext_t));
	} else if (one_in_chance(2)) {
		if (tmp_uc) {
			free(tmp_uc);
			tmp_uc = NULL;
		}
		tmp_uc = malloc(sizeof(ucontext_t));
		ucp->uc_link = tmp_uc;
		/* Trying to cause a major page fault at Kernel level */
		madvise(ucp->uc_link, sizeof(ucontext_t), MADV_DONTNEED);
	}

	if (args & ARG_MESS_WITH_MSR_AT) {
		/* Changing the checkpointed registers */
		if (one_in_chance(4)) {
			ucp->uc_link->uc_mcontext.gp_regs[PT_MSR] |= MSR_TS_S;
		} else {
			if (one_in_chance(2)) {
				ucp->uc_link->uc_mcontext.gp_regs[PT_MSR] |=
						 MSR_TS_T;
			} else if (one_in_chance(2)) {
				ucp->uc_link->uc_mcontext.gp_regs[PT_MSR] |=
						MSR_TS_T | MSR_TS_S;
			}
		}

		/* Checking the current register context */
		if (one_in_chance(2)) {
			ucp->uc_mcontext.gp_regs[PT_MSR] |= MSR_TS_S;
		} else if (one_in_chance(2)) {
			if (one_in_chance(2))
				ucp->uc_mcontext.gp_regs[PT_MSR] |=
					MSR_TS_T;
			else if (one_in_chance(2))
				ucp->uc_mcontext.gp_regs[PT_MSR] |=
					MSR_TS_T | MSR_TS_S;
		}
	}

	if (one_in_chance(20)) {
		/* Nested transaction start */
		if (one_in_chance(5))
			mess_with_tm();

		/* Return without changing any other context info */
		return;
	}

	if (one_in_chance(10))
		ucp->uc_mcontext.gp_regs[PT_MSR] = random();
	if (one_in_chance(10))
		ucp->uc_mcontext.gp_regs[PT_NIP] = random();
	if (one_in_chance(10))
		ucp->uc_link->uc_mcontext.gp_regs[PT_MSR] = random();
	if (one_in_chance(10))
		ucp->uc_link->uc_mcontext.gp_regs[PT_NIP] = random();

	ucp->uc_mcontext.gp_regs[PT_TRAP] = random();
	ucp->uc_mcontext.gp_regs[PT_DSISR] = random();
	ucp->uc_mcontext.gp_regs[PT_DAR] = random();
	ucp->uc_mcontext.gp_regs[PT_ORIG_R3] = random();
	ucp->uc_mcontext.gp_regs[PT_XER] = random();
	ucp->uc_mcontext.gp_regs[PT_RESULT] = random();
	ucp->uc_mcontext.gp_regs[PT_SOFTE] = random();
	ucp->uc_mcontext.gp_regs[PT_DSCR] = random();
	ucp->uc_mcontext.gp_regs[PT_CTR] = random();
	ucp->uc_mcontext.gp_regs[PT_LNK] = random();
	ucp->uc_mcontext.gp_regs[PT_CCR] = random();
	ucp->uc_mcontext.gp_regs[PT_REGS_COUNT] = random();

	ucp->uc_link->uc_mcontext.gp_regs[PT_TRAP] = random();
	ucp->uc_link->uc_mcontext.gp_regs[PT_DSISR] = random();
	ucp->uc_link->uc_mcontext.gp_regs[PT_DAR] = random();
	ucp->uc_link->uc_mcontext.gp_regs[PT_ORIG_R3] = random();
	ucp->uc_link->uc_mcontext.gp_regs[PT_XER] = random();
	ucp->uc_link->uc_mcontext.gp_regs[PT_RESULT] = random();
	ucp->uc_link->uc_mcontext.gp_regs[PT_SOFTE] = random();
	ucp->uc_link->uc_mcontext.gp_regs[PT_DSCR] = random();
	ucp->uc_link->uc_mcontext.gp_regs[PT_CTR] = random();
	ucp->uc_link->uc_mcontext.gp_regs[PT_LNK] = random();
	ucp->uc_link->uc_mcontext.gp_regs[PT_CCR] = random();
	ucp->uc_link->uc_mcontext.gp_regs[PT_REGS_COUNT] = random();

	if (args & ARG_MESS_WITH_TM_BEFORE) {
		if (one_in_chance(2))
			mess_with_tm();
	}
}