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
 int /*<<< orphan*/  ca0113_mmio_gpio_set (struct hda_codec*,int,long) ; 

__attribute__((used)) static int zxr_headphone_gain_set(struct hda_codec *codec, long val)
{
	ca0113_mmio_gpio_set(codec, 1, val);

	return 0;
}