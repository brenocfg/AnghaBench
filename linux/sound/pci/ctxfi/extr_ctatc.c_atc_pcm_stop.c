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
struct src {TYPE_1__* ops; } ;
struct ct_atc_pcm {int n_srcc; scalar_t__ started; struct src** srccs; struct src* src; int /*<<< orphan*/  timer; } ;
struct ct_atc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* commit_write ) (struct src*) ;int /*<<< orphan*/  (* set_state ) (struct src*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_bm ) (struct src*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SRC_STATE_OFF ; 
 int /*<<< orphan*/  ct_timer_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct src*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct src*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct src*) ; 
 int /*<<< orphan*/  stub4 (struct src*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct src*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct src*) ; 

__attribute__((used)) static int atc_pcm_stop(struct ct_atc *atc, struct ct_atc_pcm *apcm)
{
	struct src *src;
	int i;

	ct_timer_stop(apcm->timer);

	src = apcm->src;
	src->ops->set_bm(src, 0);
	src->ops->set_state(src, SRC_STATE_OFF);
	src->ops->commit_write(src);

	if (apcm->srccs) {
		for (i = 0; i < apcm->n_srcc; i++) {
			src = apcm->srccs[i];
			src->ops->set_bm(src, 0);
			src->ops->set_state(src, SRC_STATE_OFF);
			src->ops->commit_write(src);
		}
	}

	apcm->started = 0;

	return 0;
}