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
 int /*<<< orphan*/  snd_hda_gen_free (struct hda_codec*) ; 
 int /*<<< orphan*/  vt1708_stop_hp_work (struct hda_codec*) ; 

__attribute__((used)) static void via_free(struct hda_codec *codec)
{
	vt1708_stop_hp_work(codec);
	snd_hda_gen_free(codec);
}