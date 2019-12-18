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
struct hda_input_mux {int num_items; TYPE_1__* items; } ;
struct hda_codec {int dummy; } ;
struct TYPE_2__ {int index; int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int EINVAL ; 
 int HDA_MAX_NUM_INPUTS ; 
 int /*<<< orphan*/  codec_err (struct hda_codec*,char*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int snd_hda_add_imux_item(struct hda_codec *codec,
			  struct hda_input_mux *imux, const char *label,
			  int index, int *type_idx)
{
	int i, label_idx = 0;
	if (imux->num_items >= HDA_MAX_NUM_INPUTS) {
		codec_err(codec, "hda_codec: Too many imux items!\n");
		return -EINVAL;
	}
	for (i = 0; i < imux->num_items; i++) {
		if (!strncmp(label, imux->items[i].label, strlen(label)))
			label_idx++;
	}
	if (type_idx)
		*type_idx = label_idx;
	if (label_idx > 0)
		snprintf(imux->items[imux->num_items].label,
			 sizeof(imux->items[imux->num_items].label),
			 "%s %d", label, label_idx);
	else
		strlcpy(imux->items[imux->num_items].label, label,
			sizeof(imux->items[imux->num_items].label));
	imux->items[imux->num_items].index = index;
	imux->num_items++;
	return 0;
}