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
 int /*<<< orphan*/  activate_amp (struct hda_codec*,int /*<<< orphan*/ ,int,int,int,int) ; 
 scalar_t__ is_active_nid (struct hda_codec*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void check_and_activate_amp(struct hda_codec *codec, hda_nid_t nid,
				   int dir, int idx, int idx_to_check,
				   bool enable)
{
	/* check whether the given amp is still used by others */
	if (!enable && is_active_nid(codec, nid, dir, idx_to_check))
		return;
	activate_amp(codec, nid, dir, idx, idx_to_check, enable);
}