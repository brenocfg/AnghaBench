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
 unsigned int HDA_COMPOSE_AMP_VAL (int /*<<< orphan*/ ,int,int,int) ; 
 int is_ctl_used (struct hda_codec*,unsigned int,int) ; 

__attribute__((used)) static bool is_ctl_associated(struct hda_codec *codec, hda_nid_t nid,
			      int dir, int idx, int type)
{
	unsigned int val = HDA_COMPOSE_AMP_VAL(nid, 3, idx, dir);
	return is_ctl_used(codec, val, type);
}