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
typedef  int /*<<< orphan*/  u8 ;
struct rfcomm_session {int dummy; } ;
struct rfcomm_hdr {int /*<<< orphan*/  len; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFCOMM_UIH ; 
 int /*<<< orphan*/  __ctrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __fcs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __len8 (int /*<<< orphan*/ ) ; 
 int rfcomm_send_frame (struct rfcomm_session*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int rfcomm_send_credits(struct rfcomm_session *s, u8 addr, u8 credits)
{
	struct rfcomm_hdr *hdr;
	u8 buf[16], *ptr = buf;

	BT_DBG("%p addr %d credits %d", s, addr, credits);

	hdr = (void *) ptr; ptr += sizeof(*hdr);
	hdr->addr = addr;
	hdr->ctrl = __ctrl(RFCOMM_UIH, 1);
	hdr->len  = __len8(0);

	*ptr = credits; ptr++;

	*ptr = __fcs(buf); ptr++;

	return rfcomm_send_frame(s, buf, ptr - buf);
}