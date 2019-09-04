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
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct audio_client {int /*<<< orphan*/  stream_id; } ;
struct TYPE_5__ {int param_size; int /*<<< orphan*/  param_id; } ;
struct TYPE_4__ {int enc_cfg_blk_size; int /*<<< orphan*/  frames_per_buf; } ;
struct asm_multi_channel_pcm_enc_cfg_v2 {int is_signed; int /*<<< orphan*/ * channel_mapping; void* sample_rate; int /*<<< orphan*/  bits_per_sample; void* num_channels; TYPE_2__ encdec; TYPE_1__ encblk; } ;
struct asm_enc_cfg_blk_param_v2 {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  opcode; } ;
struct apr_pkt {TYPE_3__ hdr; } ;

/* Variables and functions */
 int APR_HDR_SIZE ; 
 int /*<<< orphan*/  ASM_PARAM_ID_ENCDEC_ENC_CFG_BLK_V2 ; 
 int /*<<< orphan*/  ASM_STREAM_CMD_SET_ENCDEC_PARAM ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct apr_pkt*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int q6asm_ac_send_cmd_sync (struct audio_client*,struct apr_pkt*) ; 
 int /*<<< orphan*/  q6asm_add_hdr (struct audio_client*,TYPE_3__*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ q6dsp_map_channels (int /*<<< orphan*/ *,void*) ; 

int q6asm_enc_cfg_blk_pcm_format_support(struct audio_client *ac,
		uint32_t rate, uint32_t channels, uint16_t bits_per_sample)
{
	struct asm_multi_channel_pcm_enc_cfg_v2  *enc_cfg;
	struct apr_pkt *pkt;
	u8 *channel_mapping;
	u32 frames_per_buf = 0;
	int pkt_size, rc;
	void *p;

	pkt_size = APR_HDR_SIZE + sizeof(*enc_cfg);
	p = kzalloc(pkt_size, GFP_KERNEL);
	if (!p)
		return -ENOMEM;

	pkt = p;
	enc_cfg = p + APR_HDR_SIZE;
	q6asm_add_hdr(ac, &pkt->hdr, pkt_size, true, ac->stream_id);

	pkt->hdr.opcode = ASM_STREAM_CMD_SET_ENCDEC_PARAM;
	enc_cfg->encdec.param_id = ASM_PARAM_ID_ENCDEC_ENC_CFG_BLK_V2;
	enc_cfg->encdec.param_size = sizeof(*enc_cfg) - sizeof(enc_cfg->encdec);
	enc_cfg->encblk.frames_per_buf = frames_per_buf;
	enc_cfg->encblk.enc_cfg_blk_size  = enc_cfg->encdec.param_size -
					sizeof(struct asm_enc_cfg_blk_param_v2);

	enc_cfg->num_channels = channels;
	enc_cfg->bits_per_sample = bits_per_sample;
	enc_cfg->sample_rate = rate;
	enc_cfg->is_signed = 1;
	channel_mapping = enc_cfg->channel_mapping;

	if (q6dsp_map_channels(channel_mapping, channels)) {
		rc = -EINVAL;
		goto err;
	}

	rc = q6asm_ac_send_cmd_sync(ac, pkt);
err:
	kfree(pkt);
	return rc;
}