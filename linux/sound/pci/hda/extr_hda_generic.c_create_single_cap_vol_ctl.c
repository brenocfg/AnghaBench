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
 int add_single_cap_ctl (struct hda_codec*,int /*<<< orphan*/ *,int,int,unsigned int,int) ; 

__attribute__((used)) static int create_single_cap_vol_ctl(struct hda_codec *codec, int idx,
				     unsigned int vol_ctl, unsigned int sw_ctl,
				     bool inv_dmic)
{
	int err;
	err = add_single_cap_ctl(codec, NULL, idx, false, vol_ctl, inv_dmic);
	if (err < 0)
		return err;
	err = add_single_cap_ctl(codec, NULL, idx, true, sw_ctl, inv_dmic);
	if (err < 0)
		return err;
	return 0;
}