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
struct se_cmd {int data_direction; } ;

/* Variables and functions */
#define  DMA_BIDIRECTIONAL 131 
#define  DMA_FROM_DEVICE 130 
#define  DMA_NONE 129 
#define  DMA_TO_DEVICE 128 

unsigned char *transport_dump_cmd_direction(struct se_cmd *cmd)
{
	switch (cmd->data_direction) {
	case DMA_NONE:
		return "NONE";
	case DMA_FROM_DEVICE:
		return "READ";
	case DMA_TO_DEVICE:
		return "WRITE";
	case DMA_BIDIRECTIONAL:
		return "BIDI";
	default:
		break;
	}

	return "UNKNOWN";
}