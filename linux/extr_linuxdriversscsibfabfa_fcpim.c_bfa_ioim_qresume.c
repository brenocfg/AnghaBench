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
struct bfa_ioim_s {int /*<<< orphan*/  itnim; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_IOIM_SM_QRESUME ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_ioim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qresumes ; 

__attribute__((used)) static void
bfa_ioim_qresume(void *cbarg)
{
	struct bfa_ioim_s *ioim = cbarg;

	bfa_stats(ioim->itnim, qresumes);
	bfa_sm_send_event(ioim, BFA_IOIM_SM_QRESUME);
}