#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_card_asihpi {TYPE_3__* pci; int /*<<< orphan*/  h_mixer; TYPE_2__* hpi; struct snd_card* card; } ;
struct snd_card {int /*<<< orphan*/  mixername; } ;
struct hpi_control {int control_type; scalar_t__ src_node_type; scalar_t__ src_node_index; scalar_t__ dst_node_type; scalar_t__ dst_node_index; int /*<<< orphan*/  h_control; } ;
typedef  int /*<<< orphan*/  prev_ctl ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {TYPE_1__* adapter; } ;
struct TYPE_4__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int EINVAL ; 
#define  HPI_CONTROL_AESEBU_RECEIVER 142 
#define  HPI_CONTROL_AESEBU_TRANSMITTER 141 
#define  HPI_CONTROL_BITSTREAM 140 
#define  HPI_CONTROL_CHANNEL_MODE 139 
#define  HPI_CONTROL_COMPANDER 138 
#define  HPI_CONTROL_CONNECTION 137 
#define  HPI_CONTROL_LEVEL 136 
#define  HPI_CONTROL_METER 135 
#define  HPI_CONTROL_MICROPHONE 134 
#define  HPI_CONTROL_MULTIPLEXER 133 
#define  HPI_CONTROL_PARAMETRIC_EQ 132 
#define  HPI_CONTROL_SAMPLECLOCK 131 
#define  HPI_CONTROL_TUNER 130 
#define  HPI_CONTROL_VOLUME 129 
#define  HPI_CONTROL_VOX 128 
 scalar_t__ HPI_DESTNODE_NONE ; 
 int HPI_ERROR_CONTROL_DISABLED ; 
 int HPI_ERROR_INVALID_OBJ_INDEX ; 
 scalar_t__ HPI_SOURCENODE_NONE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned int,...) ; 
 int /*<<< orphan*/  hpi_handle_error (int) ; 
 int hpi_mixer_get_control_by_index (int /*<<< orphan*/ ,unsigned int,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,int*,int /*<<< orphan*/ *) ; 
 int hpi_mixer_open (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct hpi_control*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mixer_dump ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_asihpi_aesebu_rx_add (struct snd_card_asihpi*,struct hpi_control*) ; 
 int snd_asihpi_aesebu_tx_add (struct snd_card_asihpi*,struct hpi_control*) ; 
 int snd_asihpi_cmode_add (struct snd_card_asihpi*,struct hpi_control*) ; 
 int snd_asihpi_level_add (struct snd_card_asihpi*,struct hpi_control*) ; 
 int snd_asihpi_meter_add (struct snd_card_asihpi*,struct hpi_control*,unsigned int) ; 
 int snd_asihpi_mux_add (struct snd_card_asihpi*,struct hpi_control*) ; 
 int snd_asihpi_sampleclock_add (struct snd_card_asihpi*,struct hpi_control*) ; 
 int snd_asihpi_tuner_add (struct snd_card_asihpi*,struct hpi_control*) ; 
 int snd_asihpi_volume_add (struct snd_card_asihpi*,struct hpi_control*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_card_asihpi_mixer_new(struct snd_card_asihpi *asihpi)
{
	struct snd_card *card;
	unsigned int idx = 0;
	unsigned int subindex = 0;
	int err;
	struct hpi_control hpi_ctl, prev_ctl;

	if (snd_BUG_ON(!asihpi))
		return -EINVAL;
	card = asihpi->card;
	strcpy(card->mixername, "Asihpi Mixer");

	err =
	    hpi_mixer_open(asihpi->hpi->adapter->index,
			  &asihpi->h_mixer);
	hpi_handle_error(err);
	if (err)
		return -err;

	memset(&prev_ctl, 0, sizeof(prev_ctl));
	prev_ctl.control_type = -1;

	for (idx = 0; idx < 2000; idx++) {
		err = hpi_mixer_get_control_by_index(
				asihpi->h_mixer,
				idx,
				&hpi_ctl.src_node_type,
				&hpi_ctl.src_node_index,
				&hpi_ctl.dst_node_type,
				&hpi_ctl.dst_node_index,
				&hpi_ctl.control_type,
				&hpi_ctl.h_control);
		if (err) {
			if (err == HPI_ERROR_CONTROL_DISABLED) {
				if (mixer_dump)
					dev_info(&asihpi->pci->dev,
						   "Disabled HPI Control(%d)\n",
						   idx);
				continue;
			} else
				break;

		}

		hpi_ctl.src_node_type -= HPI_SOURCENODE_NONE;
		hpi_ctl.dst_node_type -= HPI_DESTNODE_NONE;

		/* ASI50xx in SSX mode has multiple meters on the same node.
		   Use subindex to create distinct ALSA controls
		   for any duplicated controls.
		*/
		if ((hpi_ctl.control_type == prev_ctl.control_type) &&
		    (hpi_ctl.src_node_type == prev_ctl.src_node_type) &&
		    (hpi_ctl.src_node_index == prev_ctl.src_node_index) &&
		    (hpi_ctl.dst_node_type == prev_ctl.dst_node_type) &&
		    (hpi_ctl.dst_node_index == prev_ctl.dst_node_index))
			subindex++;
		else
			subindex = 0;

		prev_ctl = hpi_ctl;

		switch (hpi_ctl.control_type) {
		case HPI_CONTROL_VOLUME:
			err = snd_asihpi_volume_add(asihpi, &hpi_ctl);
			break;
		case HPI_CONTROL_LEVEL:
			err = snd_asihpi_level_add(asihpi, &hpi_ctl);
			break;
		case HPI_CONTROL_MULTIPLEXER:
			err = snd_asihpi_mux_add(asihpi, &hpi_ctl);
			break;
		case HPI_CONTROL_CHANNEL_MODE:
			err = snd_asihpi_cmode_add(asihpi, &hpi_ctl);
			break;
		case HPI_CONTROL_METER:
			err = snd_asihpi_meter_add(asihpi, &hpi_ctl, subindex);
			break;
		case HPI_CONTROL_SAMPLECLOCK:
			err = snd_asihpi_sampleclock_add(
						asihpi, &hpi_ctl);
			break;
		case HPI_CONTROL_CONNECTION:	/* ignore these */
			continue;
		case HPI_CONTROL_TUNER:
			err = snd_asihpi_tuner_add(asihpi, &hpi_ctl);
			break;
		case HPI_CONTROL_AESEBU_TRANSMITTER:
			err = snd_asihpi_aesebu_tx_add(asihpi, &hpi_ctl);
			break;
		case HPI_CONTROL_AESEBU_RECEIVER:
			err = snd_asihpi_aesebu_rx_add(asihpi, &hpi_ctl);
			break;
		case HPI_CONTROL_VOX:
		case HPI_CONTROL_BITSTREAM:
		case HPI_CONTROL_MICROPHONE:
		case HPI_CONTROL_PARAMETRIC_EQ:
		case HPI_CONTROL_COMPANDER:
		default:
			if (mixer_dump)
				dev_info(&asihpi->pci->dev,
					"Untranslated HPI Control (%d) %d %d %d %d %d\n",
					idx,
					hpi_ctl.control_type,
					hpi_ctl.src_node_type,
					hpi_ctl.src_node_index,
					hpi_ctl.dst_node_type,
					hpi_ctl.dst_node_index);
			continue;
		}
		if (err < 0)
			return err;
	}
	if (HPI_ERROR_INVALID_OBJ_INDEX != err)
		hpi_handle_error(err);

	dev_info(&asihpi->pci->dev, "%d mixer controls found\n", idx);

	return 0;
}