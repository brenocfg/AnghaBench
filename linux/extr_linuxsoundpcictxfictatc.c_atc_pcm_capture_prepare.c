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
struct rsc {TYPE_4__* ops; } ;
struct sum {struct rsc rsc; } ;
struct srcimp {TYPE_5__* ops; } ;
struct src {struct rsc rsc; } ;
struct ct_mixer {int /*<<< orphan*/  (* get_output_ports ) (struct ct_mixer*,int /*<<< orphan*/ ,struct rsc**,struct rsc**) ;} ;
struct ct_atc_pcm {int n_srcc; int /*<<< orphan*/  timer; struct src* src; struct srcimp** srcimps; struct amixer** amixers; TYPE_2__* substream; struct src** srccs; struct sum* mono; } ;
struct ct_atc {int rsr; int msr; struct ct_mixer* mixer; } ;
struct amixer {struct rsc rsc; TYPE_3__* ops; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* map ) (struct srcimp*,struct src*,struct rsc*) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  (* next_conj ) (struct rsc*) ;int /*<<< orphan*/  (* master ) (struct rsc*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  (* commit_raw_write ) (struct amixer*) ;int /*<<< orphan*/  (* set_sum ) (struct amixer*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* set_scale ) (struct amixer*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_input ) (struct amixer*,struct rsc*) ;int /*<<< orphan*/  (* setup ) (struct amixer*,struct rsc*,int /*<<< orphan*/ ,struct sum*) ;} ;
struct TYPE_7__ {TYPE_1__* runtime; } ;
struct TYPE_6__ {int channels; int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_VOL ; 
 int /*<<< orphan*/  MIX_PCMO_FRONT ; 
 int /*<<< orphan*/  MONO_SUM_SCALE ; 
 unsigned int atc_get_pitch (int,int /*<<< orphan*/ ) ; 
 int atc_pcm_capture_get_resources (struct ct_atc*,struct ct_atc_pcm*) ; 
 int /*<<< orphan*/  atc_pcm_release_resources (struct ct_atc*,struct ct_atc_pcm*) ; 
 int /*<<< orphan*/  ct_timer_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ct_mixer*,int /*<<< orphan*/ ,struct rsc**,struct rsc**) ; 
 int /*<<< orphan*/  stub10 (struct rsc*) ; 
 int /*<<< orphan*/  stub11 (struct srcimp*,struct src*,struct rsc*) ; 
 int /*<<< orphan*/  stub12 (struct srcimp*,struct src*,struct rsc*) ; 
 int /*<<< orphan*/  stub2 (struct amixer*,struct rsc*,int /*<<< orphan*/ ,struct sum*) ; 
 int /*<<< orphan*/  stub3 (struct srcimp*,struct src*,struct rsc*) ; 
 int /*<<< orphan*/  stub4 (struct amixer*,struct rsc*,int /*<<< orphan*/ ,struct sum*) ; 
 int /*<<< orphan*/  stub5 (struct rsc*) ; 
 int /*<<< orphan*/  stub6 (struct amixer*,struct rsc*) ; 
 int /*<<< orphan*/  stub7 (struct amixer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (struct amixer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub9 (struct amixer*) ; 

__attribute__((used)) static int atc_pcm_capture_prepare(struct ct_atc *atc, struct ct_atc_pcm *apcm)
{
	struct src *src;
	struct amixer *amixer;
	struct srcimp *srcimp;
	struct ct_mixer *mixer = atc->mixer;
	struct sum *mono;
	struct rsc *out_ports[8] = {NULL};
	int err, i, j, n_sum, multi;
	unsigned int pitch;
	int mix_base = 0, imp_base = 0;

	atc_pcm_release_resources(atc, apcm);

	/* Get needed resources. */
	err = atc_pcm_capture_get_resources(atc, apcm);
	if (err)
		return err;

	/* Connect resources */
	mixer->get_output_ports(mixer, MIX_PCMO_FRONT,
				&out_ports[0], &out_ports[1]);

	multi = apcm->substream->runtime->channels;
	if (1 == multi) {
		mono = apcm->mono;
		for (i = 0; i < 2; i++) {
			amixer = apcm->amixers[i];
			amixer->ops->setup(amixer, out_ports[i],
						MONO_SUM_SCALE, mono);
		}
		out_ports[0] = &mono->rsc;
		n_sum = 1;
		mix_base = n_sum * 2;
	}

	for (i = 0; i < apcm->n_srcc; i++) {
		src = apcm->srccs[i];
		srcimp = apcm->srcimps[imp_base+i];
		amixer = apcm->amixers[mix_base+i];
		srcimp->ops->map(srcimp, src, out_ports[i%multi]);
		amixer->ops->setup(amixer, &src->rsc, INIT_VOL, NULL);
		out_ports[i%multi] = &amixer->rsc;
	}

	pitch = atc_get_pitch((atc->rsr * atc->msr),
				apcm->substream->runtime->rate);

	if ((multi > 1) && (pitch <= 0x8000000)) {
		/* Special connection for interleaved
		 * recording with conjugate channels */
		for (i = 0; i < multi; i++) {
			out_ports[i]->ops->master(out_ports[i]);
			for (j = 0; j < atc->msr; j++) {
				amixer = apcm->amixers[apcm->n_srcc+j*multi+i];
				amixer->ops->set_input(amixer, out_ports[i]);
				amixer->ops->set_scale(amixer, INIT_VOL);
				amixer->ops->set_sum(amixer, NULL);
				amixer->ops->commit_raw_write(amixer);
				out_ports[i]->ops->next_conj(out_ports[i]);

				srcimp = apcm->srcimps[apcm->n_srcc+j*multi+i];
				srcimp->ops->map(srcimp, apcm->src,
							&amixer->rsc);
			}
		}
	} else {
		for (i = 0; i < multi; i++) {
			srcimp = apcm->srcimps[apcm->n_srcc+i];
			srcimp->ops->map(srcimp, apcm->src, out_ports[i]);
		}
	}

	ct_timer_prepare(apcm->timer);

	return 0;
}