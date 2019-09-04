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
struct TYPE_3__ {int /*<<< orphan*/  request_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  status; } ;
struct msgbuf_ioctl_resp_hdr {TYPE_1__ msg; int /*<<< orphan*/  resp_len; TYPE_2__ compl_hdr; } ;
struct brcmf_msgbuf {scalar_t__ cur_ioctlrespbuf; int /*<<< orphan*/  ioctl_resp_pktid; scalar_t__ ioctl_resp_ret_len; scalar_t__ ioctl_resp_status; } ;
typedef  scalar_t__ s16 ;

/* Variables and functions */
 int /*<<< orphan*/  brcmf_msgbuf_ioctl_resp_wake (struct brcmf_msgbuf*) ; 
 int /*<<< orphan*/  brcmf_msgbuf_rxbuf_ioctlresp_post (struct brcmf_msgbuf*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
brcmf_msgbuf_process_ioctl_complete(struct brcmf_msgbuf *msgbuf, void *buf)
{
	struct msgbuf_ioctl_resp_hdr *ioctl_resp;

	ioctl_resp = (struct msgbuf_ioctl_resp_hdr *)buf;

	msgbuf->ioctl_resp_status =
			(s16)le16_to_cpu(ioctl_resp->compl_hdr.status);
	msgbuf->ioctl_resp_ret_len = le16_to_cpu(ioctl_resp->resp_len);
	msgbuf->ioctl_resp_pktid = le32_to_cpu(ioctl_resp->msg.request_id);

	brcmf_msgbuf_ioctl_resp_wake(msgbuf);

	if (msgbuf->cur_ioctlrespbuf)
		msgbuf->cur_ioctlrespbuf--;
	brcmf_msgbuf_rxbuf_ioctlresp_post(msgbuf);
}