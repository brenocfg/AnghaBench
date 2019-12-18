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
struct sum_mgr {int (* get_src ) (struct sum_mgr*,struct src_desc*,struct src**) ;int (* get_srcimp ) (struct sum_mgr*,struct srcimp_desc*,struct srcimp**) ;int (* get_sum ) (struct sum_mgr*,struct sum_desc*,struct sum**) ;} ;
struct sum_desc {int /*<<< orphan*/  msr; int /*<<< orphan*/  member_0; } ;
struct sum {int dummy; } ;
struct srcimp_mgr {int (* get_src ) (struct sum_mgr*,struct src_desc*,struct src**) ;int (* get_srcimp ) (struct sum_mgr*,struct srcimp_desc*,struct srcimp**) ;int (* get_sum ) (struct sum_mgr*,struct sum_desc*,struct sum**) ;} ;
struct srcimp_desc {int msr; int /*<<< orphan*/  member_0; } ;
struct srcimp {int dummy; } ;
struct src_mgr {int (* get_src ) (struct sum_mgr*,struct src_desc*,struct src**) ;int (* get_srcimp ) (struct sum_mgr*,struct srcimp_desc*,struct srcimp**) ;int (* get_sum ) (struct sum_mgr*,struct sum_desc*,struct sum**) ;} ;
struct src_desc {int multi; int /*<<< orphan*/  mode; int /*<<< orphan*/  msr; int /*<<< orphan*/  member_0; } ;
struct src {int dummy; } ;
struct daio_mgr {int (* get_daio ) (struct daio_mgr*,struct daio_desc*,struct daio**) ;} ;
struct daio_desc {int type; int /*<<< orphan*/  msr; int /*<<< orphan*/  member_0; } ;
struct daio {int dummy; } ;
struct ct_atc {scalar_t__ model; scalar_t__ n_pcm; int /*<<< orphan*/ * pcm; int /*<<< orphan*/  msr; struct sum_mgr** rsc_mgrs; scalar_t__ n_srcimp; int /*<<< orphan*/ * srcimps; scalar_t__ n_src; int /*<<< orphan*/ * srcs; scalar_t__ n_daio; TYPE_1__* card; int /*<<< orphan*/ * daios; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCRW ; 
 scalar_t__ CTSB073X ; 
 scalar_t__ CTSB1270 ; 
 size_t DAIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SPDIFI1 ; 
 int SPDIFIO ; 
 size_t SRC ; 
 size_t SRCIMP ; 
 size_t SUM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int stub1 (struct daio_mgr*,struct daio_desc*,struct daio**) ; 
 int stub2 (struct sum_mgr*,struct src_desc*,struct src**) ; 
 int stub3 (struct sum_mgr*,struct srcimp_desc*,struct srcimp**) ; 
 int stub4 (struct sum_mgr*,struct sum_desc*,struct sum**) ; 

__attribute__((used)) static int atc_get_resources(struct ct_atc *atc)
{
	struct daio_desc da_desc = {0};
	struct daio_mgr *daio_mgr;
	struct src_desc src_dsc = {0};
	struct src_mgr *src_mgr;
	struct srcimp_desc srcimp_dsc = {0};
	struct srcimp_mgr *srcimp_mgr;
	struct sum_desc sum_dsc = {0};
	struct sum_mgr *sum_mgr;
	int err, i, num_srcs, num_daios;

	num_daios = ((atc->model == CTSB1270) ? 8 : 7);
	num_srcs = ((atc->model == CTSB1270) ? 6 : 4);

	atc->daios = kcalloc(num_daios, sizeof(void *), GFP_KERNEL);
	if (!atc->daios)
		return -ENOMEM;

	atc->srcs = kcalloc(num_srcs, sizeof(void *), GFP_KERNEL);
	if (!atc->srcs)
		return -ENOMEM;

	atc->srcimps = kcalloc(num_srcs, sizeof(void *), GFP_KERNEL);
	if (!atc->srcimps)
		return -ENOMEM;

	atc->pcm = kcalloc(2 * 4, sizeof(void *), GFP_KERNEL);
	if (!atc->pcm)
		return -ENOMEM;

	daio_mgr = (struct daio_mgr *)atc->rsc_mgrs[DAIO];
	da_desc.msr = atc->msr;
	for (i = 0, atc->n_daio = 0; i < num_daios; i++) {
		da_desc.type = (atc->model != CTSB073X) ? i :
			     ((i == SPDIFIO) ? SPDIFI1 : i);
		err = daio_mgr->get_daio(daio_mgr, &da_desc,
					(struct daio **)&atc->daios[i]);
		if (err) {
			dev_err(atc->card->dev,
				"Failed to get DAIO resource %d!!!\n",
				i);
			return err;
		}
		atc->n_daio++;
	}

	src_mgr = atc->rsc_mgrs[SRC];
	src_dsc.multi = 1;
	src_dsc.msr = atc->msr;
	src_dsc.mode = ARCRW;
	for (i = 0, atc->n_src = 0; i < num_srcs; i++) {
		err = src_mgr->get_src(src_mgr, &src_dsc,
					(struct src **)&atc->srcs[i]);
		if (err)
			return err;

		atc->n_src++;
	}

	srcimp_mgr = atc->rsc_mgrs[SRCIMP];
	srcimp_dsc.msr = 8;
	for (i = 0, atc->n_srcimp = 0; i < num_srcs; i++) {
		err = srcimp_mgr->get_srcimp(srcimp_mgr, &srcimp_dsc,
					(struct srcimp **)&atc->srcimps[i]);
		if (err)
			return err;

		atc->n_srcimp++;
	}

	sum_mgr = atc->rsc_mgrs[SUM];
	sum_dsc.msr = atc->msr;
	for (i = 0, atc->n_pcm = 0; i < (2*4); i++) {
		err = sum_mgr->get_sum(sum_mgr, &sum_dsc,
					(struct sum **)&atc->pcm[i]);
		if (err)
			return err;

		atc->n_pcm++;
	}

	return 0;
}