#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct airo_info {TYPE_1__* dev; } ;
typedef  int /*<<< orphan*/  payloadLen ;
typedef  int /*<<< orphan*/  cmd ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_9__ {int parm0; int /*<<< orphan*/  cmd; } ;
struct TYPE_8__ {int status; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ Resp ;
typedef  TYPE_3__ Cmd ;

/* Variables and functions */
 int /*<<< orphan*/  BAP1 ; 
 int /*<<< orphan*/  CMD_TRANSMIT ; 
 int ERROR ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  airo_print_warn (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ bap_setup (struct airo_info*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bap_write (struct airo_info*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int header_len (int /*<<< orphan*/ ) ; 
 scalar_t__ issuecommand (struct airo_info*,TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int transmit_802_11_packet(struct airo_info *ai, int len, char *pPacket)
{
	__le16 fc, payloadLen;
	Cmd cmd;
	Resp rsp;
	int hdrlen;
	static u8 tail[(30-10) + 2 + 6] = {[30-10] = 6};
	/* padding of header to full size + le16 gaplen (6) + gaplen bytes */
	u16 txFid = len;
	len >>= 16;

	fc = *(__le16*)pPacket;
	hdrlen = header_len(fc);

	if (len < hdrlen) {
		airo_print_warn(ai->dev->name, "Short packet %d", len);
		return ERROR;
	}

	/* packet is 802.11 header +  payload
	 * write the payload length and dst/src/payload */
	if (bap_setup(ai, txFid, 6, BAP1) != SUCCESS) return ERROR;
	/* The 802.11 header aren't counted as part of the payload, so
	 * we have to subtract the header bytes off */
	payloadLen = cpu_to_le16(len-hdrlen);
	bap_write(ai, &payloadLen, sizeof(payloadLen),BAP1);
	if (bap_setup(ai, txFid, 0x0014, BAP1) != SUCCESS) return ERROR;
	bap_write(ai, (__le16 *)pPacket, hdrlen, BAP1);
	bap_write(ai, (__le16 *)(tail + (hdrlen - 10)), 38 - hdrlen, BAP1);

	bap_write(ai, (__le16 *)(pPacket + hdrlen), len - hdrlen, BAP1);
	// issue the transmit command
	memset( &cmd, 0, sizeof( cmd ) );
	cmd.cmd = CMD_TRANSMIT;
	cmd.parm0 = txFid;
	if (issuecommand(ai, &cmd, &rsp) != SUCCESS) return ERROR;
	if ( (rsp.status & 0xFF00) != 0) return ERROR;
	return SUCCESS;
}