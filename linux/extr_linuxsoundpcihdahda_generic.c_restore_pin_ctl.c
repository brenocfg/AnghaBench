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
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  snd_hda_codec_get_pin_target (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_pin_ctl (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void restore_pin_ctl(struct hda_codec *codec, hda_nid_t pin)
{
	update_pin_ctl(codec, pin, snd_hda_codec_get_pin_target(codec, pin));
}