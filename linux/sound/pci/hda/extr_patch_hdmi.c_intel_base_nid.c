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
struct TYPE_2__ {int vendor_id; } ;
struct hda_codec {TYPE_1__ core; } ;

/* Variables and functions */

__attribute__((used)) static int intel_base_nid(struct hda_codec *codec)
{
	switch (codec->core.vendor_id) {
	case 0x80860054: /* ILK */
	case 0x80862804: /* ILK */
	case 0x80862882: /* VLV */
		return 4;
	default:
		return 5;
	}
}