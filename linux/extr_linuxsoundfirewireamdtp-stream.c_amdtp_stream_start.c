#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct amdtp_stream {int data_block_quadlets; scalar_t__ direction; unsigned int data_block_state; size_t sfc; unsigned int syt_offset_state; int flags; scalar_t__ packet_index; int callbacked; int /*<<< orphan*/  mutex; TYPE_1__* unit; int /*<<< orphan*/  buffer; int /*<<< orphan*/  context; int /*<<< orphan*/  tag; int /*<<< orphan*/  max_payload_length; int /*<<< orphan*/  last_syt_offset; scalar_t__ data_block_counter; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_13__ {int /*<<< orphan*/  card; } ;
struct TYPE_12__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ AMDTP_IN_STREAM ; 
 int CIP_EMPTY_WITH_TAG0 ; 
 int CIP_NO_HEADER ; 
#define  CIP_SFC_176400 134 
#define  CIP_SFC_192000 133 
#define  CIP_SFC_32000 132 
#define  CIP_SFC_44100 131 
#define  CIP_SFC_48000 130 
#define  CIP_SFC_88200 129 
#define  CIP_SFC_96000 128 
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 int EBADFD ; 
 int EBUSY ; 
 int /*<<< orphan*/  ERR_PTR (int) ; 
 int FW_ISO_CONTEXT_MATCH_TAG0 ; 
 int FW_ISO_CONTEXT_MATCH_TAG1 ; 
 int FW_ISO_CONTEXT_RECEIVE ; 
 int FW_ISO_CONTEXT_TRANSMIT ; 
 unsigned int IN_PACKET_HEADER_SIZE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 unsigned int OUT_PACKET_HEADER_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QUEUE_LENGTH ; 
 int /*<<< orphan*/  TAG_CIP ; 
 int /*<<< orphan*/  TAG_NO_CIP_HEADER ; 
 int /*<<< orphan*/  TICKS_PER_CYCLE ; 
 scalar_t__ UINT_MAX ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  amdtp_stream_first_callback ; 
 int /*<<< orphan*/  amdtp_stream_get_max_payload (struct amdtp_stream*) ; 
 scalar_t__ amdtp_stream_running (struct amdtp_stream*) ; 
 int /*<<< orphan*/  amdtp_stream_update (struct amdtp_stream*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fw_iso_context_create (int /*<<< orphan*/ ,int,int,int,unsigned int,int /*<<< orphan*/ ,struct amdtp_stream*) ; 
 int /*<<< orphan*/  fw_iso_context_destroy (int /*<<< orphan*/ ) ; 
 int fw_iso_context_start (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* fw_parent_device (TYPE_1__*) ; 
 int /*<<< orphan*/  iso_packets_buffer_destroy (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int iso_packets_buffer_init (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int queue_in_packet (struct amdtp_stream*) ; 
 int queue_out_packet (struct amdtp_stream*,int /*<<< orphan*/ ) ; 

int amdtp_stream_start(struct amdtp_stream *s, int channel, int speed)
{
	static const struct {
		unsigned int data_block;
		unsigned int syt_offset;
	} initial_state[] = {
		[CIP_SFC_32000]  = {  4, 3072 },
		[CIP_SFC_48000]  = {  6, 1024 },
		[CIP_SFC_96000]  = { 12, 1024 },
		[CIP_SFC_192000] = { 24, 1024 },
		[CIP_SFC_44100]  = {  0,   67 },
		[CIP_SFC_88200]  = {  0,   67 },
		[CIP_SFC_176400] = {  0,   67 },
	};
	unsigned int header_size;
	enum dma_data_direction dir;
	int type, tag, err;

	mutex_lock(&s->mutex);

	if (WARN_ON(amdtp_stream_running(s) ||
		    (s->data_block_quadlets < 1))) {
		err = -EBADFD;
		goto err_unlock;
	}

	if (s->direction == AMDTP_IN_STREAM)
		s->data_block_counter = UINT_MAX;
	else
		s->data_block_counter = 0;
	s->data_block_state = initial_state[s->sfc].data_block;
	s->syt_offset_state = initial_state[s->sfc].syt_offset;
	s->last_syt_offset = TICKS_PER_CYCLE;

	/* initialize packet buffer */
	if (s->direction == AMDTP_IN_STREAM) {
		dir = DMA_FROM_DEVICE;
		type = FW_ISO_CONTEXT_RECEIVE;
		header_size = IN_PACKET_HEADER_SIZE;
	} else {
		dir = DMA_TO_DEVICE;
		type = FW_ISO_CONTEXT_TRANSMIT;
		header_size = OUT_PACKET_HEADER_SIZE;
	}
	err = iso_packets_buffer_init(&s->buffer, s->unit, QUEUE_LENGTH,
				      amdtp_stream_get_max_payload(s), dir);
	if (err < 0)
		goto err_unlock;

	s->context = fw_iso_context_create(fw_parent_device(s->unit)->card,
					   type, channel, speed, header_size,
					   amdtp_stream_first_callback, s);
	if (IS_ERR(s->context)) {
		err = PTR_ERR(s->context);
		if (err == -EBUSY)
			dev_err(&s->unit->device,
				"no free stream on this controller\n");
		goto err_buffer;
	}

	amdtp_stream_update(s);

	if (s->direction == AMDTP_IN_STREAM)
		s->max_payload_length = amdtp_stream_get_max_payload(s);

	if (s->flags & CIP_NO_HEADER)
		s->tag = TAG_NO_CIP_HEADER;
	else
		s->tag = TAG_CIP;

	s->packet_index = 0;
	do {
		if (s->direction == AMDTP_IN_STREAM)
			err = queue_in_packet(s);
		else
			err = queue_out_packet(s, 0);
		if (err < 0)
			goto err_context;
	} while (s->packet_index > 0);

	/* NOTE: TAG1 matches CIP. This just affects in stream. */
	tag = FW_ISO_CONTEXT_MATCH_TAG1;
	if ((s->flags & CIP_EMPTY_WITH_TAG0) || (s->flags & CIP_NO_HEADER))
		tag |= FW_ISO_CONTEXT_MATCH_TAG0;

	s->callbacked = false;
	err = fw_iso_context_start(s->context, -1, 0, tag);
	if (err < 0)
		goto err_context;

	mutex_unlock(&s->mutex);

	return 0;

err_context:
	fw_iso_context_destroy(s->context);
	s->context = ERR_PTR(-1);
err_buffer:
	iso_packets_buffer_destroy(&s->buffer, s->unit);
err_unlock:
	mutex_unlock(&s->mutex);

	return err;
}