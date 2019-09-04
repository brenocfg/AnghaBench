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
struct hda_codec {int /*<<< orphan*/  core; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 unsigned int snd_hdac_codec_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,unsigned int,unsigned int) ; 

__attribute__((used)) static inline unsigned int
snd_hda_codec_read(struct hda_codec *codec, hda_nid_t nid,
				int flags,
				unsigned int verb, unsigned int parm)
{
	return snd_hdac_codec_read(&codec->core, nid, flags, verb, parm);
}