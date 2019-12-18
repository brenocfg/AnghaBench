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
struct hda_codec {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * vals; } ;

/* Variables and functions */
 TYPE_1__* ae5_headphone_gain_presets ; 
 int /*<<< orphan*/  ca0113_mmio_command_set (struct hda_codec*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ae5_headphone_gain_set(struct hda_codec *codec, long val)
{
	unsigned int i;

	for (i = 0; i < 4; i++)
		ca0113_mmio_command_set(codec, 0x48, 0x11 + i,
				ae5_headphone_gain_presets[val].vals[i]);
	return 0;
}