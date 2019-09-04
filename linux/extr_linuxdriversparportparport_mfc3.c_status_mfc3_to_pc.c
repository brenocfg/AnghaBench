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

/* Variables and functions */
 unsigned char PARPORT_STATUS_ACK ; 
 unsigned char PARPORT_STATUS_BUSY ; 
 unsigned char PARPORT_STATUS_ERROR ; 
 unsigned char PARPORT_STATUS_PAPEROUT ; 
 unsigned char PARPORT_STATUS_SELECT ; 

__attribute__((used)) static unsigned char status_mfc3_to_pc(unsigned char status)
{
	unsigned char ret = PARPORT_STATUS_BUSY;

	if (status & 1) /* Busy */
		ret &= ~PARPORT_STATUS_BUSY;
	if (status & 2) /* PaperOut */
		ret |= PARPORT_STATUS_PAPEROUT;
	if (status & 4) /* Selected */
		ret |= PARPORT_STATUS_SELECT;
	if (status & 8) /* Ack */
		ret |= PARPORT_STATUS_ACK;
	if (status & 16) /* /ERROR */
		ret |= PARPORT_STATUS_ERROR;

	return ret;
}