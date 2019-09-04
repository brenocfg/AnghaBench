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
struct sense_iu {int /*<<< orphan*/  tag; } ;
struct usbg_cmd {struct f_uas* fu; int /*<<< orphan*/  tag; struct sense_iu sense_iu; struct uas_stream* stream; } ;
struct uas_stream {TYPE_1__* req_status; } ;
struct f_uas {int /*<<< orphan*/  ep_status; } ;
struct TYPE_2__ {struct usbg_cmd* context; int /*<<< orphan*/  complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasp_prepare_status (struct usbg_cmd*) ; 
 int /*<<< orphan*/  uasp_status_data_cmpl ; 
 int usb_ep_queue (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uasp_send_status_response(struct usbg_cmd *cmd)
{
	struct f_uas *fu = cmd->fu;
	struct uas_stream *stream = cmd->stream;
	struct sense_iu *iu = &cmd->sense_iu;

	iu->tag = cpu_to_be16(cmd->tag);
	stream->req_status->complete = uasp_status_data_cmpl;
	stream->req_status->context = cmd;
	cmd->fu = fu;
	uasp_prepare_status(cmd);
	return usb_ep_queue(fu->ep_status, stream->req_status, GFP_ATOMIC);
}