#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {unsigned short buf_ptr; unsigned char buf_base; } ;
struct TYPE_10__ {scalar_t__ virt_addr; } ;
struct TYPE_9__ {TYPE_1__** port_array; scalar_t__ memory_base; } ;
struct TYPE_8__ {unsigned long last_mem_alloc; } ;
typedef  TYPE_2__ SLMP_INFO ;
typedef  TYPE_3__ SCADESC_EX ;
typedef  TYPE_4__ SCADESC ;

/* Variables and functions */
 scalar_t__ SCABUFSIZE ; 

__attribute__((used)) static int alloc_frame_bufs(SLMP_INFO *info, SCADESC *buf_list,SCADESC_EX *buf_list_ex,int count)
{
	int i;
	unsigned long phys_addr;

	for ( i = 0; i < count; i++ ) {
		buf_list_ex[i].virt_addr = info->memory_base + info->port_array[0]->last_mem_alloc;
		phys_addr = info->port_array[0]->last_mem_alloc;
		info->port_array[0]->last_mem_alloc += SCABUFSIZE;

		buf_list[i].buf_ptr  = (unsigned short)phys_addr;
		buf_list[i].buf_base = (unsigned char)(phys_addr >> 16);
	}

	return 0;
}