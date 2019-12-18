#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct srcimp {TYPE_2__* ops; } ;
struct src_mgr {int /*<<< orphan*/  (* commit_write ) (struct src_mgr*) ;int /*<<< orphan*/  (* src_enable_s ) (struct src_mgr*,struct src*) ;int /*<<< orphan*/  (* src_disable ) (struct src_mgr*,struct src*) ;} ;
struct src {int /*<<< orphan*/  rsc; TYPE_3__* ops; } ;
struct rsc {int dummy; } ;
struct TYPE_5__ {struct rsc rscr; struct rsc rscl; } ;
struct dai {TYPE_4__* ops; TYPE_1__ daio; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* commit_write ) (struct dai*) ;int /*<<< orphan*/  (* set_enb_srt ) (struct dai*,int) ;int /*<<< orphan*/  (* set_enb_src ) (struct dai*,int) ;int /*<<< orphan*/  (* set_srt_srcr ) (struct dai*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* set_srt_srcl ) (struct dai*,int /*<<< orphan*/ *) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  (* commit_write ) (struct src*) ;int /*<<< orphan*/  (* set_state ) (struct src*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_pm ) (struct src*,int) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  (* map ) (struct srcimp*,struct src*,struct rsc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SRC_STATE_RUN ; 
 int /*<<< orphan*/  stub1 (struct srcimp*,struct src*,struct rsc*) ; 
 int /*<<< orphan*/  stub10 (struct dai*,int) ; 
 int /*<<< orphan*/  stub11 (struct dai*,int) ; 
 int /*<<< orphan*/  stub12 (struct dai*) ; 
 int /*<<< orphan*/  stub13 (struct src_mgr*) ; 
 int /*<<< orphan*/  stub2 (struct src_mgr*,struct src*) ; 
 int /*<<< orphan*/  stub3 (struct src_mgr*) ; 
 int /*<<< orphan*/  stub4 (struct src*,int) ; 
 int /*<<< orphan*/  stub5 (struct src*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct src*) ; 
 int /*<<< orphan*/  stub7 (struct src_mgr*,struct src*) ; 
 int /*<<< orphan*/  stub8 (struct dai*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub9 (struct dai*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
atc_connect_dai(struct src_mgr *src_mgr, struct dai *dai,
		struct src **srcs, struct srcimp **srcimps)
{
	struct rsc *rscs[2] = {NULL};
	struct src *src;
	struct srcimp *srcimp;
	int i = 0;

	rscs[0] = &dai->daio.rscl;
	rscs[1] = &dai->daio.rscr;
	for (i = 0; i < 2; i++) {
		src = srcs[i];
		srcimp = srcimps[i];
		srcimp->ops->map(srcimp, src, rscs[i]);
		src_mgr->src_disable(src_mgr, src);
	}

	src_mgr->commit_write(src_mgr); /* Actually disable SRCs */

	src = srcs[0];
	src->ops->set_pm(src, 1);
	for (i = 0; i < 2; i++) {
		src = srcs[i];
		src->ops->set_state(src, SRC_STATE_RUN);
		src->ops->commit_write(src);
		src_mgr->src_enable_s(src_mgr, src);
	}

	dai->ops->set_srt_srcl(dai, &(srcs[0]->rsc));
	dai->ops->set_srt_srcr(dai, &(srcs[1]->rsc));

	dai->ops->set_enb_src(dai, 1);
	dai->ops->set_enb_srt(dai, 1);
	dai->ops->commit_write(dai);

	src_mgr->commit_write(src_mgr); /* Synchronously enable SRCs */
}