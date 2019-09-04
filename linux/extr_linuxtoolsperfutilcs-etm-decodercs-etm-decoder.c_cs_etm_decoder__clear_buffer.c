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
struct cs_etm_decoder {TYPE_1__* packet_buffer; scalar_t__ packet_count; scalar_t__ tail; scalar_t__ head; } ;
struct TYPE_2__ {int last_instr_taken_branch; int exc; int exc_ret; int /*<<< orphan*/  cpu; void* end_addr; void* start_addr; } ;

/* Variables and functions */
 void* CS_ETM_INVAL_ADDR ; 
 int /*<<< orphan*/  INT_MIN ; 
 int MAX_BUFFER ; 

__attribute__((used)) static void cs_etm_decoder__clear_buffer(struct cs_etm_decoder *decoder)
{
	int i;

	decoder->head = 0;
	decoder->tail = 0;
	decoder->packet_count = 0;
	for (i = 0; i < MAX_BUFFER; i++) {
		decoder->packet_buffer[i].start_addr = CS_ETM_INVAL_ADDR;
		decoder->packet_buffer[i].end_addr = CS_ETM_INVAL_ADDR;
		decoder->packet_buffer[i].last_instr_taken_branch = false;
		decoder->packet_buffer[i].exc = false;
		decoder->packet_buffer[i].exc_ret = false;
		decoder->packet_buffer[i].cpu = INT_MIN;
	}
}