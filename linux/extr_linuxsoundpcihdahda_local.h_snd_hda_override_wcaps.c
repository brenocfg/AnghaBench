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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ start_nid; scalar_t__ num_nodes; } ;
struct hda_codec {TYPE_1__ core; int /*<<< orphan*/ * wcaps; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */

__attribute__((used)) static inline void snd_hda_override_wcaps(struct hda_codec *codec,
					  hda_nid_t nid, u32 val)
{
	if (nid >= codec->core.start_nid &&
	    nid < codec->core.start_nid + codec->core.num_nodes)
		codec->wcaps[nid - codec->core.start_nid] = val;
}