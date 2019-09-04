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
typedef  int /*<<< orphan*/  uint32_t ;
struct phy_packet {int dummy; } ;
struct TYPE_3__ {size_t tcode; } ;
struct link_packet {TYPE_1__ common; } ;
struct TYPE_4__ {int type; } ;

/* Variables and functions */
#define  PACKET_OTHER 131 
#define  PACKET_REQUEST 130 
#define  PACKET_RESERVED 129 
#define  PACKET_RESPONSE 128 
 int /*<<< orphan*/  clear_pending_transaction_list () ; 
 int handle_request_packet (int /*<<< orphan*/ *,size_t) ; 
 int handle_response_packet (int /*<<< orphan*/ *,size_t) ; 
 TYPE_2__* packet_info ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
handle_packet(uint32_t *data, size_t length)
{
	if (length == 0) {
		printf("bus reset\r\n");
		clear_pending_transaction_list();
	} else if (length > sizeof(struct phy_packet)) {
		struct link_packet *p = (struct link_packet *) data;

		switch (packet_info[p->common.tcode].type) {
		case PACKET_REQUEST:
			return handle_request_packet(data, length);

		case PACKET_RESPONSE:
			return handle_response_packet(data, length);

		case PACKET_OTHER:
		case PACKET_RESERVED:
			return 0;
		}
	}

	return 1;
}