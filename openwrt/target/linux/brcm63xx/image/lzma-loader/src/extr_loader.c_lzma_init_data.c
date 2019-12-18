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
 int /*<<< orphan*/  LOADADDR ; 
 int /*<<< orphan*/  kernel_la ; 
 unsigned char* lzma_data ; 
 int lzma_datasize ; 

__attribute__((used)) static void lzma_init_data(void)
{
	extern unsigned char _lzma_data_start[];
	extern unsigned char _lzma_data_end[];

	kernel_la = LOADADDR;
	lzma_data = _lzma_data_start;
	lzma_datasize = _lzma_data_end - _lzma_data_start;
}