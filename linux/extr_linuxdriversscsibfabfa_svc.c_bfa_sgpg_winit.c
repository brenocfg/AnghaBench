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
struct bfa_sgpg_wqe_s {void (* cbfn ) (void*) ;void* cbarg; int /*<<< orphan*/  sgpg_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

void
bfa_sgpg_winit(struct bfa_sgpg_wqe_s *wqe, void (*cbfn) (void *cbarg),
		   void *cbarg)
{
	INIT_LIST_HEAD(&wqe->sgpg_q);
	wqe->cbfn = cbfn;
	wqe->cbarg = cbarg;
}