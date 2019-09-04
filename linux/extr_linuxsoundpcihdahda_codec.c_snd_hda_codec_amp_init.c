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
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct hda_codec {TYPE_1__ core; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int snd_hda_codec_amp_read (struct hda_codec*,int /*<<< orphan*/ ,int,int,int) ; 
 int snd_hda_codec_amp_update (struct hda_codec*,int /*<<< orphan*/ ,int,int,int,int,int) ; 

int snd_hda_codec_amp_init(struct hda_codec *codec, hda_nid_t nid, int ch,
			   int dir, int idx, int mask, int val)
{
	int orig;

	if (!codec->core.regmap)
		return -EINVAL;
	regcache_cache_only(codec->core.regmap, true);
	orig = snd_hda_codec_amp_read(codec, nid, ch, dir, idx);
	regcache_cache_only(codec->core.regmap, false);
	if (orig >= 0)
		return 0;
	return snd_hda_codec_amp_update(codec, nid, ch, dir, idx, mask, val);
}