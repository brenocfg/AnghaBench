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
struct wm_adsp_compr {TYPE_2__* dsp; } ;
struct snd_compr_stream {TYPE_1__* runtime; } ;
struct snd_compr_caps {int num_codecs; int /*<<< orphan*/  max_fragments; int /*<<< orphan*/  min_fragments; int /*<<< orphan*/  max_fragment_size; int /*<<< orphan*/  min_fragment_size; int /*<<< orphan*/  direction; int /*<<< orphan*/ * codecs; } ;
struct TYPE_8__ {int num_caps; int /*<<< orphan*/  compr_direction; TYPE_3__* caps; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int fw; } ;
struct TYPE_5__ {struct wm_adsp_compr* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM_ADSP_MAX_FRAGMENTS ; 
 int /*<<< orphan*/  WM_ADSP_MAX_FRAGMENT_SIZE ; 
 int /*<<< orphan*/  WM_ADSP_MIN_FRAGMENTS ; 
 int /*<<< orphan*/  WM_ADSP_MIN_FRAGMENT_SIZE ; 
 TYPE_4__* wm_adsp_fw ; 

int wm_adsp_compr_get_caps(struct snd_compr_stream *stream,
			   struct snd_compr_caps *caps)
{
	struct wm_adsp_compr *compr = stream->runtime->private_data;
	int fw = compr->dsp->fw;
	int i;

	if (wm_adsp_fw[fw].caps) {
		for (i = 0; i < wm_adsp_fw[fw].num_caps; i++)
			caps->codecs[i] = wm_adsp_fw[fw].caps[i].id;

		caps->num_codecs = i;
		caps->direction = wm_adsp_fw[fw].compr_direction;

		caps->min_fragment_size = WM_ADSP_MIN_FRAGMENT_SIZE;
		caps->max_fragment_size = WM_ADSP_MAX_FRAGMENT_SIZE;
		caps->min_fragments = WM_ADSP_MIN_FRAGMENTS;
		caps->max_fragments = WM_ADSP_MAX_FRAGMENTS;
	}

	return 0;
}