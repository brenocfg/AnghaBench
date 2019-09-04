#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct link_transaction {TYPE_4__* request; } ;
struct avc_frame {int cts; } ;
struct TYPE_6__ {unsigned long long offset_low; scalar_t__ tcode; scalar_t__ offset_high; } ;
struct TYPE_5__ {scalar_t__ data; } ;
struct TYPE_7__ {TYPE_2__ common; TYPE_1__ write_block; } ;
struct TYPE_8__ {TYPE_3__ packet; } ;

/* Variables and functions */
 unsigned long long CSR_FCP_COMMAND ; 
 unsigned long long CSR_FCP_RESPONSE ; 
 scalar_t__ TCODE_WRITE_BLOCK_REQUEST ; 
 int /*<<< orphan*/  decode_avc (struct link_transaction*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
decode_fcp(struct link_transaction *t)
{
	struct avc_frame *frame =
	    (struct avc_frame *) t->request->packet.write_block.data;
	unsigned long long offset =
	    ((unsigned long long) t->request->packet.common.offset_high << 32) |
	    t->request->packet.common.offset_low;

	if (t->request->packet.common.tcode != TCODE_WRITE_BLOCK_REQUEST)
		return 0;

	if (offset == CSR_FCP_COMMAND || offset == CSR_FCP_RESPONSE) {
		switch (frame->cts) {
		case 0x00:
			decode_avc(t);
			break;
		case 0x01:
			printf("cal fcp frame (cts=0x01)\n");
			break;
		case 0x02:
			printf("ehs fcp frame (cts=0x02)\n");
			break;
		case 0x03:
			printf("havi fcp frame (cts=0x03)\n");
			break;
		case 0x0e:
			printf("vendor specific fcp frame (cts=0x0e)\n");
			break;
		case 0x0f:
			printf("extended cts\n");
			break;
		default:
			printf("reserved fcp frame (ctx=0x%02x)\n", frame->cts);
			break;
		}
		return 1;
	}

	return 0;
}