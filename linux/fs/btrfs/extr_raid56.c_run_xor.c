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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_XOR_BLOCKS ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xor_blocks (int,int /*<<< orphan*/ ,void*,void**) ; 

__attribute__((used)) static void run_xor(void **pages, int src_cnt, ssize_t len)
{
	int src_off = 0;
	int xor_src_cnt = 0;
	void *dest = pages[src_cnt];

	while(src_cnt > 0) {
		xor_src_cnt = min(src_cnt, MAX_XOR_BLOCKS);
		xor_blocks(xor_src_cnt, len, dest, pages + src_off);

		src_cnt -= xor_src_cnt;
		src_off += xor_src_cnt;
	}
}