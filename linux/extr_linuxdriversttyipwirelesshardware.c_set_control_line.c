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
struct ipw_hardware {int dummy; } ;
struct ipw_control_packet_body {int dummy; } ;
struct TYPE_4__ {int length; } ;
struct TYPE_3__ {int value; } ;
struct ipw_control_packet {TYPE_2__ header; TYPE_1__ body; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PRIO_SETUP ; 
 int TL_PROTOCOLID_COM_CTRL ; 
 int TL_PROTOCOLID_SETUP ; 
 struct ipw_control_packet* alloc_ctrl_packet (int,unsigned int,int,int) ; 
 int /*<<< orphan*/  send_packet (struct ipw_hardware*,int,TYPE_2__*) ; 

__attribute__((used)) static int set_control_line(struct ipw_hardware *hw, int prio,
			   unsigned int channel_idx, int line, int state)
{
	struct ipw_control_packet *packet;
	int protocolid = TL_PROTOCOLID_COM_CTRL;

	if (prio == PRIO_SETUP)
		protocolid = TL_PROTOCOLID_SETUP;

	packet = alloc_ctrl_packet(sizeof(struct ipw_control_packet),
			(channel_idx + 1), protocolid, line);
	if (!packet)
		return -ENOMEM;
	packet->header.length = sizeof(struct ipw_control_packet_body);
	packet->body.value = (state == 0 ? 0 : 1);
	send_packet(hw, prio, &packet->header);
	return 0;
}