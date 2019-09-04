#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct src_mgr {int (* get_src ) (struct src_mgr*,struct src_desc*,struct src**) ;int (* get_amixer ) (struct src_mgr*,struct amixer_desc*,struct amixer**) ;} ;
struct src_desc {int multi; int msr; int /*<<< orphan*/  mode; int /*<<< orphan*/  member_0; } ;
struct src {TYPE_5__* ops; int /*<<< orphan*/  rsc; } ;
struct ct_atc_pcm {int /*<<< orphan*/  timer; struct src* src; struct amixer** amixers; scalar_t__ n_amixer; TYPE_3__* substream; } ;
struct ct_atc {int msr; int rsr; int /*<<< orphan*/  atc_mutex; int /*<<< orphan*/ * pcm; int /*<<< orphan*/  card; struct src_mgr** rsc_mgrs; } ;
struct amixer_mgr {int (* get_src ) (struct src_mgr*,struct src_desc*,struct src**) ;int (* get_amixer ) (struct src_mgr*,struct amixer_desc*,struct amixer**) ;} ;
struct amixer_desc {int msr; int /*<<< orphan*/  member_0; } ;
struct amixer {TYPE_4__* ops; } ;
struct TYPE_10__ {struct src* (* next_interleave ) (struct src*) ;int /*<<< orphan*/  (* set_pm ) (struct src*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_sf ) (struct src*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_rom ) (struct src*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_pitch ) (struct src*,unsigned int) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  (* setup ) (struct amixer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {TYPE_2__* runtime; TYPE_1__* pcm; } ;
struct TYPE_7__ {int channels; int /*<<< orphan*/  format; int /*<<< orphan*/  rate; } ;
struct TYPE_6__ {int device; } ;

/* Variables and functions */
 size_t AMIXER ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_VOL ; 
 int /*<<< orphan*/  MEMRD ; 
 size_t SRC ; 
 unsigned int atc_get_pitch (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atc_pcm_release_resources (struct ct_atc*,struct ct_atc_pcm*) ; 
 int /*<<< orphan*/  convert_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ct_map_audio_buffer (struct ct_atc*,struct ct_atc_pcm*) ; 
 int /*<<< orphan*/  ct_timer_prepare (int /*<<< orphan*/ ) ; 
 struct amixer** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  select_rom (unsigned int) ; 
 int stub1 (struct src_mgr*,struct src_desc*,struct src**) ; 
 int /*<<< orphan*/  stub2 (struct src*,unsigned int) ; 
 int /*<<< orphan*/  stub3 (struct src*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct src*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct src*,int /*<<< orphan*/ ) ; 
 struct src* stub6 (struct src*) ; 
 int stub7 (struct src_mgr*,struct amixer_desc*,struct amixer**) ; 
 int /*<<< orphan*/  stub8 (struct amixer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct src* stub9 (struct src*) ; 

__attribute__((used)) static int atc_pcm_playback_prepare(struct ct_atc *atc, struct ct_atc_pcm *apcm)
{
	struct src_mgr *src_mgr = atc->rsc_mgrs[SRC];
	struct amixer_mgr *amixer_mgr = atc->rsc_mgrs[AMIXER];
	struct src_desc desc = {0};
	struct amixer_desc mix_dsc = {0};
	struct src *src;
	struct amixer *amixer;
	int err;
	int n_amixer = apcm->substream->runtime->channels, i = 0;
	int device = apcm->substream->pcm->device;
	unsigned int pitch;

	/* first release old resources */
	atc_pcm_release_resources(atc, apcm);

	/* Get SRC resource */
	desc.multi = apcm->substream->runtime->channels;
	desc.msr = atc->msr;
	desc.mode = MEMRD;
	err = src_mgr->get_src(src_mgr, &desc, (struct src **)&apcm->src);
	if (err)
		goto error1;

	pitch = atc_get_pitch(apcm->substream->runtime->rate,
						(atc->rsr * atc->msr));
	src = apcm->src;
	src->ops->set_pitch(src, pitch);
	src->ops->set_rom(src, select_rom(pitch));
	src->ops->set_sf(src, convert_format(apcm->substream->runtime->format,
					     atc->card));
	src->ops->set_pm(src, (src->ops->next_interleave(src) != NULL));

	/* Get AMIXER resource */
	n_amixer = (n_amixer < 2) ? 2 : n_amixer;
	apcm->amixers = kcalloc(n_amixer, sizeof(void *), GFP_KERNEL);
	if (!apcm->amixers) {
		err = -ENOMEM;
		goto error1;
	}
	mix_dsc.msr = atc->msr;
	for (i = 0, apcm->n_amixer = 0; i < n_amixer; i++) {
		err = amixer_mgr->get_amixer(amixer_mgr, &mix_dsc,
					(struct amixer **)&apcm->amixers[i]);
		if (err)
			goto error1;

		apcm->n_amixer++;
	}

	/* Set up device virtual mem map */
	err = ct_map_audio_buffer(atc, apcm);
	if (err < 0)
		goto error1;

	/* Connect resources */
	src = apcm->src;
	for (i = 0; i < n_amixer; i++) {
		amixer = apcm->amixers[i];
		mutex_lock(&atc->atc_mutex);
		amixer->ops->setup(amixer, &src->rsc,
					INIT_VOL, atc->pcm[i+device*2]);
		mutex_unlock(&atc->atc_mutex);
		src = src->ops->next_interleave(src);
		if (!src)
			src = apcm->src;
	}

	ct_timer_prepare(apcm->timer);

	return 0;

error1:
	atc_pcm_release_resources(atc, apcm);
	return err;
}