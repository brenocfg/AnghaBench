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
struct snd_kcontrol_new {scalar_t__ index; int /*<<< orphan*/  iface; int /*<<< orphan*/  private_value; int /*<<< orphan*/  name; } ;
struct hpi_control {size_t src_node_type; size_t dst_node_type; int src_node_index; int dst_node_index; int /*<<< orphan*/  name; int /*<<< orphan*/  h_control; } ;

/* Variables and functions */
 scalar_t__ HPI_DESTNODE_ISTREAM ; 
 scalar_t__ HPI_DESTNODE_NONE ; 
 scalar_t__ HPI_SOURCENODE_CLOCK_SOURCE ; 
 scalar_t__ HPI_SOURCENODE_NONE ; 
 scalar_t__ HPI_SOURCENODE_OSTREAM ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_IFACE_MIXER ; 
 char** asihpi_dst_names ; 
 char** asihpi_src_names ; 
 int /*<<< orphan*/  memset (struct snd_kcontrol_new*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,int,char*,...) ; 

__attribute__((used)) static void asihpi_ctl_init(struct snd_kcontrol_new *snd_control,
				struct hpi_control *hpi_ctl,
				char *name)
{
	char *dir;
	memset(snd_control, 0, sizeof(*snd_control));
	snd_control->name = hpi_ctl->name;
	snd_control->private_value = hpi_ctl->h_control;
	snd_control->iface = SNDRV_CTL_ELEM_IFACE_MIXER;
	snd_control->index = 0;

	if (hpi_ctl->src_node_type + HPI_SOURCENODE_NONE == HPI_SOURCENODE_CLOCK_SOURCE)
		dir = ""; /* clock is neither capture nor playback */
	else if (hpi_ctl->dst_node_type + HPI_DESTNODE_NONE == HPI_DESTNODE_ISTREAM)
		dir = "Capture ";  /* On or towards a PCM capture destination*/
	else if ((hpi_ctl->src_node_type + HPI_SOURCENODE_NONE != HPI_SOURCENODE_OSTREAM) &&
		(!hpi_ctl->dst_node_type))
		dir = "Capture "; /* On a source node that is not PCM playback */
	else if (hpi_ctl->src_node_type &&
		(hpi_ctl->src_node_type + HPI_SOURCENODE_NONE != HPI_SOURCENODE_OSTREAM) &&
		(hpi_ctl->dst_node_type))
		dir = "Monitor Playback "; /* Between an input and an output */
	else
		dir = "Playback "; /* PCM Playback source, or  output node */

	if (hpi_ctl->src_node_type && hpi_ctl->dst_node_type)
		sprintf(hpi_ctl->name, "%s %d %s %d %s%s",
			asihpi_src_names[hpi_ctl->src_node_type],
			hpi_ctl->src_node_index,
			asihpi_dst_names[hpi_ctl->dst_node_type],
			hpi_ctl->dst_node_index,
			dir, name);
	else if (hpi_ctl->dst_node_type) {
		sprintf(hpi_ctl->name, "%s %d %s%s",
		asihpi_dst_names[hpi_ctl->dst_node_type],
		hpi_ctl->dst_node_index,
		dir, name);
	} else {
		sprintf(hpi_ctl->name, "%s %d %s%s",
		asihpi_src_names[hpi_ctl->src_node_type],
		hpi_ctl->src_node_index,
		dir, name);
	}
	/* printk(KERN_INFO "Adding %s %d to %d ",  hpi_ctl->name,
		hpi_ctl->wSrcNodeType, hpi_ctl->wDstNodeType); */
}