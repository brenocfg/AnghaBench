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
struct snd_ca_midi {unsigned int channel; struct snd_ca0106* dev_id; int /*<<< orphan*/  get_dev_id_port; int /*<<< orphan*/  get_dev_id_card; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  interrupt_disable; int /*<<< orphan*/  interrupt_enable; int /*<<< orphan*/  output_ready; int /*<<< orphan*/  input_avail; int /*<<< orphan*/  ack; int /*<<< orphan*/  enter_uart; int /*<<< orphan*/  reset; int /*<<< orphan*/  port; int /*<<< orphan*/  ipr_rx; int /*<<< orphan*/  ipr_tx; void* rx_enable; void* tx_enable; } ;
struct snd_ca0106 {struct snd_ca_midi midi; struct snd_ca_midi midi2; } ;

/* Variables and functions */
 unsigned int CA0106_MIDI_CHAN_B ; 
 int /*<<< orphan*/  CA0106_MIDI_INPUT_AVAIL ; 
 int /*<<< orphan*/  CA0106_MIDI_OUTPUT_READY ; 
 int /*<<< orphan*/  CA0106_MPU401_ACK ; 
 int /*<<< orphan*/  CA0106_MPU401_ENTER_UART ; 
 int /*<<< orphan*/  CA0106_MPU401_RESET ; 
 void* INTE_MIDI_RX_B ; 
 void* INTE_MIDI_TX_A ; 
 void* INTE_MIDI_TX_B ; 
 int /*<<< orphan*/  IPR_MIDI_RX_A ; 
 int /*<<< orphan*/  IPR_MIDI_RX_B ; 
 int /*<<< orphan*/  IPR_MIDI_TX_A ; 
 int /*<<< orphan*/  IPR_MIDI_TX_B ; 
 int /*<<< orphan*/  MIDI_UART_A_DATA ; 
 int /*<<< orphan*/  MIDI_UART_B_DATA ; 
 int /*<<< orphan*/  ca0106_dev_id_card ; 
 int /*<<< orphan*/  ca0106_dev_id_port ; 
 int /*<<< orphan*/  ca0106_midi_interrupt_disable ; 
 int /*<<< orphan*/  ca0106_midi_interrupt_enable ; 
 int /*<<< orphan*/  ca0106_midi_read ; 
 int /*<<< orphan*/  ca0106_midi_write ; 
 int ca_midi_init (struct snd_ca0106*,struct snd_ca_midi*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_ca0106_midi(struct snd_ca0106 *chip, unsigned int channel)
{
	struct snd_ca_midi *midi;
	char *name;
	int err;

	if (channel == CA0106_MIDI_CHAN_B) {
		name = "CA0106 MPU-401 (UART) B";
		midi =  &chip->midi2;
		midi->tx_enable = INTE_MIDI_TX_B;
		midi->rx_enable = INTE_MIDI_RX_B;
		midi->ipr_tx = IPR_MIDI_TX_B;
		midi->ipr_rx = IPR_MIDI_RX_B;
		midi->port = MIDI_UART_B_DATA;
	} else {
		name = "CA0106 MPU-401 (UART)";
		midi =  &chip->midi;
		midi->tx_enable = INTE_MIDI_TX_A;
		midi->rx_enable = INTE_MIDI_TX_B;
		midi->ipr_tx = IPR_MIDI_TX_A;
		midi->ipr_rx = IPR_MIDI_RX_A;
		midi->port = MIDI_UART_A_DATA;
	}

	midi->reset = CA0106_MPU401_RESET;
	midi->enter_uart = CA0106_MPU401_ENTER_UART;
	midi->ack = CA0106_MPU401_ACK;

	midi->input_avail = CA0106_MIDI_INPUT_AVAIL;
	midi->output_ready = CA0106_MIDI_OUTPUT_READY;

	midi->channel = channel;

	midi->interrupt_enable = ca0106_midi_interrupt_enable;
	midi->interrupt_disable = ca0106_midi_interrupt_disable;

	midi->read = ca0106_midi_read;
	midi->write = ca0106_midi_write;

	midi->get_dev_id_card = ca0106_dev_id_card;
	midi->get_dev_id_port = ca0106_dev_id_port;

	midi->dev_id = chip;
	
	if ((err = ca_midi_init(chip, midi, 0, name)) < 0)
		return err;

	return 0;
}