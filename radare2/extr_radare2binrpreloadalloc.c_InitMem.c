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
 scalar_t__ allocated_mem ; 
 char* heap_end ; 
 int max_mem ; 
 scalar_t__ mcb_count ; 
 char* mem_start_p ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 

void InitMem(char *ptr, int size_in_bytes) {
	/* store the ptr and size_in_bytes in global variable */
	max_mem = size_in_bytes;
	mem_start_p = ptr;
	mcb_count = 0;
	allocated_mem = 0;
	heap_end = mem_start_p + size_in_bytes;
	memset (mem_start_p, 0x00, max_mem);
	/* This function is complete :-) */
}