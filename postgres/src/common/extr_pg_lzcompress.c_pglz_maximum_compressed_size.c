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
typedef  int int64 ;
typedef  int int32 ;

/* Variables and functions */
 int Min (int,int) ; 

int32
pglz_maximum_compressed_size(int32 rawsize, int32 total_compressed_size)
{
	int32 compressed_size;

	/*
	 * pglz uses one control bit per byte, so we need (rawsize * 9) bits. We
	 * care about bytes though, so we add 7 to make sure we include the last
	 * incomplete byte (integer division rounds down).
	 *
	 * XXX Use int64 to prevent overflow during calculation.
	 */
	compressed_size = (int32) ((int64) rawsize * 9 + 7) / 8;

	/*
	 * Maximum compressed size can't be larger than total compressed size.
	 */
	compressed_size = Min(compressed_size, total_compressed_size);

	return compressed_size;
}