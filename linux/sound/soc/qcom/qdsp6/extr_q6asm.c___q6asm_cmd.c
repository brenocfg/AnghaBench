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
struct audio_client {int stream_id; int /*<<< orphan*/  adev; } ;
struct TYPE_2__ {int /*<<< orphan*/  opcode; } ;
struct apr_pkt {TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  APR_HDR_SIZE ; 
 int /*<<< orphan*/  ASM_DATA_CMD_EOS ; 
 int /*<<< orphan*/  ASM_SESSION_CMD_PAUSE ; 
 int /*<<< orphan*/  ASM_SESSION_CMD_SUSPEND ; 
 int /*<<< orphan*/  ASM_STREAM_CMD_CLOSE ; 
 int /*<<< orphan*/  ASM_STREAM_CMD_FLUSH ; 
 int /*<<< orphan*/  ASM_STREAM_CMD_FLUSH_READBUFS ; 
#define  CMD_CLOSE 133 
#define  CMD_EOS 132 
#define  CMD_FLUSH 131 
#define  CMD_OUT_FLUSH 130 
#define  CMD_PAUSE 129 
#define  CMD_SUSPEND 128 
 int EINVAL ; 
 int apr_send_pkt (int /*<<< orphan*/ ,struct apr_pkt*) ; 
 int q6asm_ac_send_cmd_sync (struct audio_client*,struct apr_pkt*) ; 
 int /*<<< orphan*/  q6asm_add_hdr (struct audio_client*,TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  q6asm_reset_buf_state (struct audio_client*) ; 

__attribute__((used)) static int __q6asm_cmd(struct audio_client *ac, int cmd, bool wait)
{
	int stream_id = ac->stream_id;
	struct apr_pkt pkt;
	int rc;

	q6asm_add_hdr(ac, &pkt.hdr, APR_HDR_SIZE, true, stream_id);

	switch (cmd) {
	case CMD_PAUSE:
		pkt.hdr.opcode = ASM_SESSION_CMD_PAUSE;
		break;
	case CMD_SUSPEND:
		pkt.hdr.opcode = ASM_SESSION_CMD_SUSPEND;
		break;
	case CMD_FLUSH:
		pkt.hdr.opcode = ASM_STREAM_CMD_FLUSH;
		break;
	case CMD_OUT_FLUSH:
		pkt.hdr.opcode = ASM_STREAM_CMD_FLUSH_READBUFS;
		break;
	case CMD_EOS:
		pkt.hdr.opcode = ASM_DATA_CMD_EOS;
		break;
	case CMD_CLOSE:
		pkt.hdr.opcode = ASM_STREAM_CMD_CLOSE;
		break;
	default:
		return -EINVAL;
	}

	if (wait)
		rc = q6asm_ac_send_cmd_sync(ac, &pkt);
	else
		return apr_send_pkt(ac->adev, &pkt);

	if (rc < 0)
		return rc;

	if (cmd == CMD_FLUSH)
		q6asm_reset_buf_state(ac);

	return 0;
}