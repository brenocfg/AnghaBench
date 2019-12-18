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
struct audio_port_data {size_t dsp_buf; size_t num_periods; int /*<<< orphan*/  mem_map_handle; struct audio_buffer* buf; } ;
struct audio_client {int /*<<< orphan*/  adev; int /*<<< orphan*/  lock; int /*<<< orphan*/  stream_id; struct audio_port_data* port; } ;
struct audio_buffer {int /*<<< orphan*/  size; int /*<<< orphan*/  phys; } ;
struct asm_data_cmd_read_v2 {size_t seq_id; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  mem_map_handle; int /*<<< orphan*/  buf_addr_msw; int /*<<< orphan*/  buf_addr_lsw; } ;
struct TYPE_2__ {size_t token; int /*<<< orphan*/  opcode; } ;
struct apr_pkt {TYPE_1__ hdr; } ;

/* Variables and functions */
 int APR_HDR_SIZE ; 
 int /*<<< orphan*/  ASM_DATA_CMD_READ_V2 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 int apr_send_pkt (int /*<<< orphan*/ ,struct apr_pkt*) ; 
 int /*<<< orphan*/  kfree (struct apr_pkt*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  q6asm_add_hdr (struct audio_client*,TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

int q6asm_read(struct audio_client *ac)
{
	struct asm_data_cmd_read_v2 *read;
	struct audio_port_data *port;
	struct audio_buffer *ab;
	struct apr_pkt *pkt;
	unsigned long flags;
	int pkt_size;
	int rc = 0;
	void *p;

	pkt_size = APR_HDR_SIZE + sizeof(*read);
	p = kzalloc(pkt_size, GFP_ATOMIC);
	if (!p)
		return -ENOMEM;

	pkt = p;
	read = p + APR_HDR_SIZE;

	spin_lock_irqsave(&ac->lock, flags);
	port = &ac->port[SNDRV_PCM_STREAM_CAPTURE];
	q6asm_add_hdr(ac, &pkt->hdr, pkt_size, false, ac->stream_id);
	ab = &port->buf[port->dsp_buf];
	pkt->hdr.opcode = ASM_DATA_CMD_READ_V2;
	read->buf_addr_lsw = lower_32_bits(ab->phys);
	read->buf_addr_msw = upper_32_bits(ab->phys);
	read->mem_map_handle = port->mem_map_handle;

	read->buf_size = ab->size;
	read->seq_id = port->dsp_buf;
	pkt->hdr.token = port->dsp_buf;

	port->dsp_buf++;

	if (port->dsp_buf >= port->num_periods)
		port->dsp_buf = 0;

	spin_unlock_irqrestore(&ac->lock, flags);
	rc = apr_send_pkt(ac->adev, pkt);
	if (rc == pkt_size)
		rc = 0;
	else
		pr_err("read op[0x%x]rc[%d]\n", pkt->hdr.opcode, rc);

	kfree(pkt);
	return rc;
}