#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sum_mgr {int (* get_src ) (struct sum_mgr*,struct src_desc*,struct src**) ;int (* get_amixer ) (struct sum_mgr*,struct amixer_desc*,struct amixer**) ;int (* get_sum ) (struct sum_mgr*,struct sum_desc*,struct sum**) ;int (* get_srcimp ) (struct sum_mgr*,struct srcimp_desc*,struct srcimp**) ;} ;
struct sum_desc {int msr; int /*<<< orphan*/  member_0; } ;
struct sum {int dummy; } ;
struct srcimp_mgr {int (* get_src ) (struct sum_mgr*,struct src_desc*,struct src**) ;int (* get_amixer ) (struct sum_mgr*,struct amixer_desc*,struct amixer**) ;int (* get_sum ) (struct sum_mgr*,struct sum_desc*,struct sum**) ;int (* get_srcimp ) (struct sum_mgr*,struct srcimp_desc*,struct srcimp**) ;} ;
struct srcimp_desc {int msr; int /*<<< orphan*/  member_0; } ;
struct srcimp {int dummy; } ;
struct src_node_conf_t {int msr; unsigned int pitch; int mix_msr; int imp_msr; int /*<<< orphan*/  vo; int /*<<< orphan*/  member_0; } ;
struct src_mgr {int (* get_src ) (struct sum_mgr*,struct src_desc*,struct src**) ;int (* get_amixer ) (struct sum_mgr*,struct amixer_desc*,struct amixer**) ;int (* get_sum ) (struct sum_mgr*,struct sum_desc*,struct sum**) ;int (* get_srcimp ) (struct sum_mgr*,struct srcimp_desc*,struct srcimp**) ;} ;
struct src_desc {int multi; int msr; int /*<<< orphan*/  mode; int /*<<< orphan*/  member_0; } ;
struct src {TYPE_3__* ops; } ;
struct ct_atc_pcm {struct src* src; TYPE_2__* substream; scalar_t__ n_srcimp; struct srcimp** srcimps; int /*<<< orphan*/  mono; scalar_t__ n_amixer; int /*<<< orphan*/ * amixers; scalar_t__ n_srcc; struct src** srccs; } ;
struct ct_atc {int rsr; int msr; struct sum_mgr** rsc_mgrs; } ;
struct amixer_mgr {int (* get_src ) (struct sum_mgr*,struct src_desc*,struct src**) ;int (* get_amixer ) (struct sum_mgr*,struct amixer_desc*,struct amixer**) ;int (* get_sum ) (struct sum_mgr*,struct sum_desc*,struct sum**) ;int (* get_srcimp ) (struct sum_mgr*,struct srcimp_desc*,struct srcimp**) ;} ;
struct amixer_desc {int msr; int /*<<< orphan*/  member_0; } ;
struct amixer {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_pitch ) (struct src*,unsigned int) ;int /*<<< orphan*/  (* set_vo ) (struct src*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_rom ) (struct src*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__* runtime; } ;
struct TYPE_4__ {int channels; int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 size_t AMIXER ; 
 int /*<<< orphan*/  ARCRW ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MEMWR ; 
 size_t SRC ; 
 size_t SRCIMP ; 
 size_t SUM ; 
 unsigned int atc_get_pitch (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atc_pcm_release_resources (struct ct_atc*,struct ct_atc_pcm*) ; 
 int ct_map_audio_buffer (struct ct_atc*,struct ct_atc_pcm*) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  select_rom (unsigned int) ; 
 int /*<<< orphan*/  setup_src_node_conf (struct ct_atc*,struct ct_atc_pcm*,struct src_node_conf_t*,int*) ; 
 int stub1 (struct sum_mgr*,struct src_desc*,struct src**) ; 
 int /*<<< orphan*/  stub2 (struct src*,unsigned int) ; 
 int /*<<< orphan*/  stub3 (struct src*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct src*,int /*<<< orphan*/ ) ; 
 int stub5 (struct sum_mgr*,struct amixer_desc*,struct amixer**) ; 
 int stub6 (struct sum_mgr*,struct sum_desc*,struct sum**) ; 
 int stub7 (struct sum_mgr*,struct srcimp_desc*,struct srcimp**) ; 
 int stub8 (struct sum_mgr*,struct src_desc*,struct src**) ; 
 int /*<<< orphan*/  stub9 (struct src*,unsigned int) ; 

__attribute__((used)) static int
atc_pcm_capture_get_resources(struct ct_atc *atc, struct ct_atc_pcm *apcm)
{
	struct src_mgr *src_mgr = atc->rsc_mgrs[SRC];
	struct srcimp_mgr *srcimp_mgr = atc->rsc_mgrs[SRCIMP];
	struct amixer_mgr *amixer_mgr = atc->rsc_mgrs[AMIXER];
	struct sum_mgr *sum_mgr = atc->rsc_mgrs[SUM];
	struct src_desc src_dsc = {0};
	struct src *src;
	struct srcimp_desc srcimp_dsc = {0};
	struct srcimp *srcimp;
	struct amixer_desc mix_dsc = {0};
	struct sum_desc sum_dsc = {0};
	unsigned int pitch;
	int multi, err, i;
	int n_srcimp, n_amixer, n_srcc, n_sum;
	struct src_node_conf_t src_node_conf[2] = {{0} };

	/* first release old resources */
	atc_pcm_release_resources(atc, apcm);

	/* The numbers of converting SRCs and SRCIMPs should be determined
	 * by pitch value. */

	multi = apcm->substream->runtime->channels;

	/* get pitch and convert to fixed-point 8.24 format. */
	pitch = atc_get_pitch((atc->rsr * atc->msr),
				apcm->substream->runtime->rate);

	setup_src_node_conf(atc, apcm, src_node_conf, &n_srcc);
	n_sum = (1 == multi) ? 1 : 0;
	n_amixer = n_sum * 2 + n_srcc;
	n_srcimp = n_srcc;
	if ((multi > 1) && (0x8000000 >= pitch)) {
		/* Need extra AMIXERs and SRCIMPs for special treatment
		 * of interleaved recording of conjugate channels */
		n_amixer += multi * atc->msr;
		n_srcimp += multi * atc->msr;
	} else {
		n_srcimp += multi;
	}

	if (n_srcc) {
		apcm->srccs = kcalloc(n_srcc, sizeof(void *), GFP_KERNEL);
		if (!apcm->srccs)
			return -ENOMEM;
	}
	if (n_amixer) {
		apcm->amixers = kcalloc(n_amixer, sizeof(void *), GFP_KERNEL);
		if (!apcm->amixers) {
			err = -ENOMEM;
			goto error1;
		}
	}
	apcm->srcimps = kcalloc(n_srcimp, sizeof(void *), GFP_KERNEL);
	if (!apcm->srcimps) {
		err = -ENOMEM;
		goto error1;
	}

	/* Allocate SRCs for sample rate conversion if needed */
	src_dsc.multi = 1;
	src_dsc.mode = ARCRW;
	for (i = 0, apcm->n_srcc = 0; i < n_srcc; i++) {
		src_dsc.msr = src_node_conf[i/multi].msr;
		err = src_mgr->get_src(src_mgr, &src_dsc,
					(struct src **)&apcm->srccs[i]);
		if (err)
			goto error1;

		src = apcm->srccs[i];
		pitch = src_node_conf[i/multi].pitch;
		src->ops->set_pitch(src, pitch);
		src->ops->set_rom(src, select_rom(pitch));
		src->ops->set_vo(src, src_node_conf[i/multi].vo);

		apcm->n_srcc++;
	}

	/* Allocate AMIXERs for routing SRCs of conversion if needed */
	for (i = 0, apcm->n_amixer = 0; i < n_amixer; i++) {
		if (i < (n_sum*2))
			mix_dsc.msr = atc->msr;
		else if (i < (n_sum*2+n_srcc))
			mix_dsc.msr = src_node_conf[(i-n_sum*2)/multi].mix_msr;
		else
			mix_dsc.msr = 1;

		err = amixer_mgr->get_amixer(amixer_mgr, &mix_dsc,
					(struct amixer **)&apcm->amixers[i]);
		if (err)
			goto error1;

		apcm->n_amixer++;
	}

	/* Allocate a SUM resource to mix all input channels together */
	sum_dsc.msr = atc->msr;
	err = sum_mgr->get_sum(sum_mgr, &sum_dsc, (struct sum **)&apcm->mono);
	if (err)
		goto error1;

	pitch = atc_get_pitch((atc->rsr * atc->msr),
				apcm->substream->runtime->rate);
	/* Allocate SRCIMP resources */
	for (i = 0, apcm->n_srcimp = 0; i < n_srcimp; i++) {
		if (i < (n_srcc))
			srcimp_dsc.msr = src_node_conf[i/multi].imp_msr;
		else if (1 == multi)
			srcimp_dsc.msr = (pitch <= 0x8000000) ? atc->msr : 1;
		else
			srcimp_dsc.msr = 1;

		err = srcimp_mgr->get_srcimp(srcimp_mgr, &srcimp_dsc, &srcimp);
		if (err)
			goto error1;

		apcm->srcimps[i] = srcimp;
		apcm->n_srcimp++;
	}

	/* Allocate a SRC for writing data to host memory */
	src_dsc.multi = apcm->substream->runtime->channels;
	src_dsc.msr = 1;
	src_dsc.mode = MEMWR;
	err = src_mgr->get_src(src_mgr, &src_dsc, (struct src **)&apcm->src);
	if (err)
		goto error1;

	src = apcm->src;
	src->ops->set_pitch(src, pitch);

	/* Set up device virtual mem map */
	err = ct_map_audio_buffer(atc, apcm);
	if (err < 0)
		goto error1;

	return 0;

error1:
	atc_pcm_release_resources(atc, apcm);
	return err;
}