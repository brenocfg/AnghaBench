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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  fls (scalar_t__) ; 
 scalar_t__ jhash_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8
htable_bits(u32 hashsize)
{
	/* Assume that hashsize == 2^htable_bits */
	u8 bits = fls(hashsize - 1);

	if (jhash_size(bits) != hashsize)
		/* Round up to the first 2^n value */
		bits = fls(hashsize);

	return bits;
}