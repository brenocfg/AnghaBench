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

__attribute__((used)) static inline
int hda_call_check_power_status(struct hda_codec *codec, hda_nid_t nid)
{
#ifdef CONFIG_PM
	if (codec->patch_ops.check_power_status)
		return codec->patch_ops.check_power_status(codec, nid);
#endif
	return 0;
}