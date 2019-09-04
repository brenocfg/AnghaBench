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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 int SMC_BUF_MIN_SIZE ; 
 scalar_t__ SMC_RMBE_SIZES ; 
 scalar_t__ ilog2 (int) ; 

__attribute__((used)) static u8 smc_compress_bufsize(int size)
{
	u8 compressed;

	if (size <= SMC_BUF_MIN_SIZE)
		return 0;

	size = (size - 1) >> 14;
	compressed = ilog2(size) + 1;
	if (compressed >= SMC_RMBE_SIZES)
		compressed = SMC_RMBE_SIZES - 1;
	return compressed;
}