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
struct TYPE_2__ {int /*<<< orphan*/ * cleanup; int /*<<< orphan*/ * prepare; int /*<<< orphan*/ * close; int /*<<< orphan*/ * open; } ;
struct hda_pcm_stream {TYPE_1__ ops; scalar_t__ nid; int /*<<< orphan*/  maxbps; int /*<<< orphan*/  formats; int /*<<< orphan*/  rates; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/ * hda_pcm_default_cleanup ; 
 void* hda_pcm_default_open_close ; 
 int /*<<< orphan*/ * hda_pcm_default_prepare ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_hda_query_supported_pcm (struct hda_codec*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_pcm_default_values(struct hda_codec *codec,
				  struct hda_pcm_stream *info)
{
	int err;

	/* query support PCM information from the given NID */
	if (info->nid && (!info->rates || !info->formats)) {
		err = snd_hda_query_supported_pcm(codec, info->nid,
				info->rates ? NULL : &info->rates,
				info->formats ? NULL : &info->formats,
				info->maxbps ? NULL : &info->maxbps);
		if (err < 0)
			return err;
	}
	if (info->ops.open == NULL)
		info->ops.open = hda_pcm_default_open_close;
	if (info->ops.close == NULL)
		info->ops.close = hda_pcm_default_open_close;
	if (info->ops.prepare == NULL) {
		if (snd_BUG_ON(!info->nid))
			return -EINVAL;
		info->ops.prepare = hda_pcm_default_prepare;
	}
	if (info->ops.cleanup == NULL) {
		if (snd_BUG_ON(!info->nid))
			return -EINVAL;
		info->ops.cleanup = hda_pcm_default_cleanup;
	}
	return 0;
}