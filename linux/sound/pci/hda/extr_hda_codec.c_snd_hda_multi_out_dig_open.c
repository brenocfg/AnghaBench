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
struct hda_multi_out {scalar_t__ dig_out_used; int /*<<< orphan*/  dig_out_nid; } ;
struct hda_codec {int /*<<< orphan*/  spdif_mutex; } ;

/* Variables and functions */
 scalar_t__ HDA_DIG_ANALOG_DUP ; 
 scalar_t__ HDA_DIG_EXCLUSIVE ; 
 int /*<<< orphan*/  cleanup_dig_out_stream (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int snd_hda_multi_out_dig_open(struct hda_codec *codec,
			       struct hda_multi_out *mout)
{
	mutex_lock(&codec->spdif_mutex);
	if (mout->dig_out_used == HDA_DIG_ANALOG_DUP)
		/* already opened as analog dup; reset it once */
		cleanup_dig_out_stream(codec, mout->dig_out_nid);
	mout->dig_out_used = HDA_DIG_EXCLUSIVE;
	mutex_unlock(&codec->spdif_mutex);
	return 0;
}