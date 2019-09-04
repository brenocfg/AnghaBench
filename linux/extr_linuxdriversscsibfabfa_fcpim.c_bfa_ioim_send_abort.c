#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bfi_ioim_abort_req_s {int /*<<< orphan*/  mh; scalar_t__ abort_tag; int /*<<< orphan*/  io_tag; } ;
struct bfa_ioim_s {int /*<<< orphan*/  reqq; int /*<<< orphan*/  bfa; scalar_t__ abort_tag; int /*<<< orphan*/  iotag; TYPE_1__* iosp; } ;
typedef  enum bfi_ioim_h2i { ____Placeholder_bfi_ioim_h2i } bfi_ioim_h2i ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;
struct TYPE_2__ {scalar_t__ abort_explicit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int BFI_IOIM_H2I_IOABORT_REQ ; 
 int BFI_IOIM_H2I_IOCLEANUP_REQ ; 
 int /*<<< orphan*/  BFI_MC_IOIM ; 
 int /*<<< orphan*/  bfa_fn_lpu (int /*<<< orphan*/ ) ; 
 struct bfi_ioim_abort_req_s* bfa_reqq_next (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_reqq_produce (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static	bfa_boolean_t
bfa_ioim_send_abort(struct bfa_ioim_s *ioim)
{
	struct bfi_ioim_abort_req_s *m;
	enum bfi_ioim_h2i	msgop;

	/*
	 * check for room in queue to send request now
	 */
	m = bfa_reqq_next(ioim->bfa, ioim->reqq);
	if (!m)
		return BFA_FALSE;

	/*
	 * build i/o request message next
	 */
	if (ioim->iosp->abort_explicit)
		msgop = BFI_IOIM_H2I_IOABORT_REQ;
	else
		msgop = BFI_IOIM_H2I_IOCLEANUP_REQ;

	bfi_h2i_set(m->mh, BFI_MC_IOIM, msgop, bfa_fn_lpu(ioim->bfa));
	m->io_tag    = cpu_to_be16(ioim->iotag);
	m->abort_tag = ++ioim->abort_tag;

	/*
	 * queue I/O message to firmware
	 */
	bfa_reqq_produce(ioim->bfa, ioim->reqq, m->mh);
	return BFA_TRUE;
}