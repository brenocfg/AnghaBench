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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static void bytewise_xor(void *_bo, const void *_bi1, const void *_bi2,
			 size_t size)
{
	u8 *bo = _bo;
	const u8 *bi1 = _bi1, *bi2 = _bi2;
	size_t itr;
	for (itr = 0; itr < size; itr++)
		bo[itr] = bi1[itr] ^ bi2[itr];
}