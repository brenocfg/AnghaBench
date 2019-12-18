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
#define  LZMA_RESULT_DATA_ERROR 128 
 int LZMA_RESULT_OK ; 
 int /*<<< orphan*/  board_init () ; 
 int /*<<< orphan*/  flush_cache (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halt () ; 
 int kernel_la ; 
 int lzma_decompress (unsigned char*) ; 
 int /*<<< orphan*/  lzma_init_data () ; 
 int lzma_init_props () ; 
 int /*<<< orphan*/  lzma_outsize ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void loader_main(unsigned long reg_a0, unsigned long reg_a1,
		 unsigned long reg_a2, unsigned long reg_a3)
{
	void (*kernel_entry) (unsigned long, unsigned long, unsigned long,
			      unsigned long);
	int res;

	board_init();

	printf("\n\nOpenWrt kernel loader for BCM63XX\n");
	printf("Copyright (C) 2011 Gabor Juhos <juhosg@openwrt.org>\n");
	printf("Copyright (C) 2014 Jonas Gorski <jogo@openwrt.org>\n");

	lzma_init_data();

	res = lzma_init_props();
	if (res != LZMA_RESULT_OK) {
		printf("Incorrect LZMA stream properties!\n");
		halt();
	}

	printf("Decompressing kernel... ");

	res = lzma_decompress((unsigned char *) kernel_la);
	if (res != LZMA_RESULT_OK) {
		printf("failed, ");
		switch (res) {
		case LZMA_RESULT_DATA_ERROR:
			printf("data error!\n");
			break;
		default:
			printf("unknown error %d!\n", res);
		}
		halt();
	} else {
		printf("done!\n");
	}

	flush_cache(kernel_la, lzma_outsize);

	printf("Starting kernel at %08x...\n\n", kernel_la);

	kernel_entry = (void *) kernel_la;
	kernel_entry(reg_a0, reg_a1, reg_a2, reg_a3);
}