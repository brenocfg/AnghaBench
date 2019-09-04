#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct snd_kcontrol {int /*<<< orphan*/  private_value; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; scalar_t__ item; scalar_t__ items; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_info {int count; TYPE_2__ value; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 size_t HPI_SOURCENODE_NONE ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_ENUMERATED ; 
 char** asihpi_src_names ; 
 int hpi_multiplexer_query_source (int /*<<< orphan*/ ,scalar_t__,size_t*,size_t*) ; 
 scalar_t__ snd_card_asihpi_mux_count_sources (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,size_t) ; 

__attribute__((used)) static int snd_asihpi_mux_info(struct snd_kcontrol *kcontrol,
			       struct snd_ctl_elem_info *uinfo)
{
	int err;
	u16 src_node_type, src_node_index;
	u32 h_control = kcontrol->private_value;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	uinfo->value.enumerated.items =
	    snd_card_asihpi_mux_count_sources(kcontrol);

	if (uinfo->value.enumerated.item >= uinfo->value.enumerated.items)
		uinfo->value.enumerated.item =
		    uinfo->value.enumerated.items - 1;

	err =
	    hpi_multiplexer_query_source(h_control,
					uinfo->value.enumerated.item,
					&src_node_type, &src_node_index);

	sprintf(uinfo->value.enumerated.name, "%s %d",
		asihpi_src_names[src_node_type - HPI_SOURCENODE_NONE],
		src_node_index);
	return 0;
}