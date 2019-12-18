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
struct snd_rawmidi_substream {int dummy; } ;
struct snd_ff {int* rx_bytes; int /*<<< orphan*/ * transactions; int /*<<< orphan*/ * msg_buf; int /*<<< orphan*/ * next_ktime; TYPE_2__* spec; int /*<<< orphan*/ * rx_midi_work; scalar_t__* rx_midi_error; int /*<<< orphan*/  unit; int /*<<< orphan*/ * rx_midi_substreams; } ;
struct fw_device {int generation; int /*<<< orphan*/  max_speed; int /*<<< orphan*/  node_id; int /*<<< orphan*/  card; } ;
typedef  int /*<<< orphan*/  fw_transaction_callback_t ;
struct TYPE_4__ {unsigned long long* midi_rx_addrs; TYPE_1__* protocol; } ;
struct TYPE_3__ {int (* fill_midi_msg ) (struct snd_ff*,struct snd_rawmidi_substream*,unsigned int) ;} ;

/* Variables and functions */
 int NSEC_PER_SEC ; 
 struct snd_rawmidi_substream* READ_ONCE (int /*<<< orphan*/ ) ; 
 int TCODE_WRITE_BLOCK_REQUEST ; 
 int TCODE_WRITE_QUADLET_REQUEST ; 
 int /*<<< orphan*/  finish_transmit_midi0_msg ; 
 int /*<<< orphan*/  finish_transmit_midi1_msg ; 
 struct fw_device* fw_parent_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_send_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ktime_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ snd_rawmidi_transmit_empty (struct snd_rawmidi_substream*) ; 
 int stub1 (struct snd_ff*,struct snd_rawmidi_substream*,unsigned int) ; 

__attribute__((used)) static void transmit_midi_msg(struct snd_ff *ff, unsigned int port)
{
	struct snd_rawmidi_substream *substream =
			READ_ONCE(ff->rx_midi_substreams[port]);
	int quad_count;

	struct fw_device *fw_dev = fw_parent_device(ff->unit);
	unsigned long long addr;
	int generation;
	fw_transaction_callback_t callback;
	int tcode;

	if (substream == NULL || snd_rawmidi_transmit_empty(substream))
		return;

	if (ff->rx_bytes[port] > 0 || ff->rx_midi_error[port])
		return;

	/* Do it in next chance. */
	if (ktime_after(ff->next_ktime[port], ktime_get())) {
		schedule_work(&ff->rx_midi_work[port]);
		return;
	}

	quad_count = ff->spec->protocol->fill_midi_msg(ff, substream, port);
	if (quad_count <= 0)
		return;

	if (port == 0) {
		addr = ff->spec->midi_rx_addrs[0];
		callback = finish_transmit_midi0_msg;
	} else {
		addr = ff->spec->midi_rx_addrs[1];
		callback = finish_transmit_midi1_msg;
	}

	/* Set interval to next transaction. */
	ff->next_ktime[port] = ktime_add_ns(ktime_get(),
				ff->rx_bytes[port] * 8 * NSEC_PER_SEC / 31250);

	if (quad_count == 1)
		tcode = TCODE_WRITE_QUADLET_REQUEST;
	else
		tcode = TCODE_WRITE_BLOCK_REQUEST;

	/*
	 * In Linux FireWire core, when generation is updated with memory
	 * barrier, node id has already been updated. In this module, After
	 * this smp_rmb(), load/store instructions to memory are completed.
	 * Thus, both of generation and node id are available with recent
	 * values. This is a light-serialization solution to handle bus reset
	 * events on IEEE 1394 bus.
	 */
	generation = fw_dev->generation;
	smp_rmb();
	fw_send_request(fw_dev->card, &ff->transactions[port], tcode,
			fw_dev->node_id, generation, fw_dev->max_speed,
			addr, &ff->msg_buf[port], quad_count * 4,
			callback, &ff->transactions[port]);
}