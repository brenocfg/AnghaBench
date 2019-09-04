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
struct audio_client {int /*<<< orphan*/  stream_id; } ;
struct asm_stream_cmd_open_read_v3 {int mode_flags; int /*<<< orphan*/  enc_cfg_id; int /*<<< orphan*/  bits_per_sample; int /*<<< orphan*/  preprocopo_id; int /*<<< orphan*/  src_endpointype; } ;
struct TYPE_2__ {int /*<<< orphan*/  opcode; } ;
struct apr_pkt {TYPE_1__ hdr; } ;

/* Variables and functions */
 int APR_HDR_SIZE ; 
 int /*<<< orphan*/  ASM_END_POINT_DEVICE_MATRIX ; 
 int ASM_LEGACY_STREAM_SESSION ; 
 int /*<<< orphan*/  ASM_MEDIA_FMT_MULTI_CHANNEL_PCM_V2 ; 
 int ASM_SHIFT_STREAM_PERF_MODE_FLAG_IN_OPEN_READ ; 
 int /*<<< orphan*/  ASM_STREAM_CMD_OPEN_READ_V3 ; 
 int /*<<< orphan*/  ASM_STREAM_POSTPROC_TOPO_ID_NONE ; 
 int ENOMEM ; 
#define  FORMAT_LINEAR_PCM 128 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct apr_pkt*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int q6asm_ac_send_cmd_sync (struct audio_client*,struct apr_pkt*) ; 
 int /*<<< orphan*/  q6asm_add_hdr (struct audio_client*,TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __q6asm_open_read(struct audio_client *ac,
		uint32_t format, uint16_t bits_per_sample)
{
	struct asm_stream_cmd_open_read_v3 *open;
	struct apr_pkt *pkt;
	int pkt_size, rc;
	void *p;

	pkt_size = APR_HDR_SIZE + sizeof(*open);
	p = kzalloc(pkt_size, GFP_KERNEL);
	if (!p)
		return -ENOMEM;

	pkt = p;
	open = p + APR_HDR_SIZE;

	q6asm_add_hdr(ac, &pkt->hdr,  pkt_size, true, ac->stream_id);
	pkt->hdr.opcode = ASM_STREAM_CMD_OPEN_READ_V3;
	/* Stream prio : High, provide meta info with encoded frames */
	open->src_endpointype = ASM_END_POINT_DEVICE_MATRIX;

	open->preprocopo_id = ASM_STREAM_POSTPROC_TOPO_ID_NONE;
	open->bits_per_sample = bits_per_sample;
	open->mode_flags = 0x0;

	open->mode_flags |= ASM_LEGACY_STREAM_SESSION <<
				ASM_SHIFT_STREAM_PERF_MODE_FLAG_IN_OPEN_READ;

	switch (format) {
	case FORMAT_LINEAR_PCM:
		open->mode_flags |= 0x00;
		open->enc_cfg_id = ASM_MEDIA_FMT_MULTI_CHANNEL_PCM_V2;
		break;
	default:
		pr_err("Invalid format[%d]\n", format);
	}

	rc = q6asm_ac_send_cmd_sync(ac, pkt);

	kfree(pkt);
	return rc;
}