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
struct daio_mgr {int /*<<< orphan*/  (* commit_write ) (struct daio_mgr*) ;int /*<<< orphan*/  (* daio_disable ) (struct daio_mgr*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* daio_enable ) (struct daio_mgr*,int /*<<< orphan*/ ) ;} ;
struct ct_atc {int /*<<< orphan*/ * daios; struct daio_mgr** rsc_mgrs; } ;

/* Variables and functions */
 size_t DAIO ; 
 int /*<<< orphan*/  stub1 (struct daio_mgr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct daio_mgr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct daio_mgr*) ; 

__attribute__((used)) static int atc_daio_unmute(struct ct_atc *atc, unsigned char state, int type)
{
	struct daio_mgr *daio_mgr = atc->rsc_mgrs[DAIO];

	if (state)
		daio_mgr->daio_enable(daio_mgr, atc->daios[type]);
	else
		daio_mgr->daio_disable(daio_mgr, atc->daios[type]);

	daio_mgr->commit_write(daio_mgr);

	return 0;
}