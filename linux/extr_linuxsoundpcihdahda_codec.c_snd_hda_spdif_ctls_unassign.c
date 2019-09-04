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
typedef  scalar_t__ u16 ;
struct hda_spdif_out {scalar_t__ nid; } ;
struct TYPE_2__ {int used; } ;
struct hda_codec {int /*<<< orphan*/  spdif_mutex; TYPE_1__ spdif_out; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct hda_spdif_out* snd_array_elem (TYPE_1__*,int) ; 

void snd_hda_spdif_ctls_unassign(struct hda_codec *codec, int idx)
{
	struct hda_spdif_out *spdif;

	if (WARN_ON(codec->spdif_out.used <= idx))
		return;
	mutex_lock(&codec->spdif_mutex);
	spdif = snd_array_elem(&codec->spdif_out, idx);
	spdif->nid = (u16)-1;
	mutex_unlock(&codec->spdif_mutex);
}