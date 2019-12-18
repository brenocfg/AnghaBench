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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct audio_client {int /*<<< orphan*/  io_mode; int /*<<< orphan*/  dev; int /*<<< orphan*/  stream_id; } ;
struct asm_stream_cmd_open_write_v3 {int mode_flags; int /*<<< orphan*/  dec_fmt_id; int /*<<< orphan*/  postprocopo_id; int /*<<< orphan*/  bits_per_sample; int /*<<< orphan*/  sink_endpointype; } ;
struct TYPE_2__ {int /*<<< orphan*/  opcode; } ;
struct apr_pkt {TYPE_1__ hdr; } ;

/* Variables and functions */
 int APR_HDR_SIZE ; 
 int /*<<< orphan*/  ASM_END_POINT_DEVICE_MATRIX ; 
 int ASM_LEGACY_STREAM_SESSION ; 
 int /*<<< orphan*/  ASM_MEDIA_FMT_MP3 ; 
 int /*<<< orphan*/  ASM_MEDIA_FMT_MULTI_CHANNEL_PCM_V2 ; 
 int /*<<< orphan*/  ASM_NULL_POPP_TOPOLOGY ; 
 int /*<<< orphan*/  ASM_STREAM_CMD_OPEN_WRITE_V3 ; 
 int /*<<< orphan*/  ASM_TUN_WRITE_IO_MODE ; 
 int EINVAL ; 
 int ENOMEM ; 
#define  FORMAT_LINEAR_PCM 129 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  SND_AUDIOCODEC_MP3 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (struct apr_pkt*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int q6asm_ac_send_cmd_sync (struct audio_client*,struct apr_pkt*) ; 
 int /*<<< orphan*/  q6asm_add_hdr (struct audio_client*,TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 

int q6asm_open_write(struct audio_client *ac, uint32_t format,
		     uint16_t bits_per_sample)
{
	struct asm_stream_cmd_open_write_v3 *open;
	struct apr_pkt *pkt;
	void *p;
	int rc, pkt_size;

	pkt_size = APR_HDR_SIZE + sizeof(*open);

	p = kzalloc(pkt_size, GFP_KERNEL);
	if (!p)
		return -ENOMEM;

	pkt = p;
	open = p + APR_HDR_SIZE;
	q6asm_add_hdr(ac, &pkt->hdr, pkt_size, true, ac->stream_id);

	pkt->hdr.opcode = ASM_STREAM_CMD_OPEN_WRITE_V3;
	open->mode_flags = 0x00;
	open->mode_flags |= ASM_LEGACY_STREAM_SESSION;

	/* source endpoint : matrix */
	open->sink_endpointype = ASM_END_POINT_DEVICE_MATRIX;
	open->bits_per_sample = bits_per_sample;
	open->postprocopo_id = ASM_NULL_POPP_TOPOLOGY;

	switch (format) {
	case SND_AUDIOCODEC_MP3:
		open->dec_fmt_id = ASM_MEDIA_FMT_MP3;
		break;
	case FORMAT_LINEAR_PCM:
		open->dec_fmt_id = ASM_MEDIA_FMT_MULTI_CHANNEL_PCM_V2;
		break;
	default:
		dev_err(ac->dev, "Invalid format 0x%x\n", format);
		rc = -EINVAL;
		goto err;
	}

	rc = q6asm_ac_send_cmd_sync(ac, pkt);
	if (rc < 0)
		goto err;

	ac->io_mode |= ASM_TUN_WRITE_IO_MODE;

err:
	kfree(pkt);
	return rc;
}