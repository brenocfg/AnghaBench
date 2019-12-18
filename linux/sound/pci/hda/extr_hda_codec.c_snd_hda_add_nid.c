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
struct TYPE_2__ {int /*<<< orphan*/  index; int /*<<< orphan*/  name; } ;
struct snd_kcontrol {TYPE_1__ id; } ;
struct hda_nid_item {unsigned int index; scalar_t__ nid; struct snd_kcontrol* kctl; } ;
struct hda_codec {int /*<<< orphan*/  nids; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  codec_err (struct hda_codec*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct hda_nid_item* snd_array_new (int /*<<< orphan*/ *) ; 

int snd_hda_add_nid(struct hda_codec *codec, struct snd_kcontrol *kctl,
		    unsigned int index, hda_nid_t nid)
{
	struct hda_nid_item *item;

	if (nid > 0) {
		item = snd_array_new(&codec->nids);
		if (!item)
			return -ENOMEM;
		item->kctl = kctl;
		item->index = index;
		item->nid = nid;
		return 0;
	}
	codec_err(codec, "no NID for mapping control %s:%d:%d\n",
		  kctl->id.name, kctl->id.index, index);
	return -EINVAL;
}