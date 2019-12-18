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
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  alc_write_coef_idx (struct hda_codec*,int,int) ; 
 int /*<<< orphan*/  snd_hda_gen_update_outputs (struct hda_codec*) ; 

__attribute__((used)) static void alc269_quanta_automute(struct hda_codec *codec)
{
	snd_hda_gen_update_outputs(codec);

	alc_write_coef_idx(codec, 0x0c, 0x680);
	alc_write_coef_idx(codec, 0x0c, 0x480);
}