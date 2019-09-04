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
 int HZ ; 
 int STP_HZ ; 
 int /*<<< orphan*/  put_unaligned_be16 (unsigned long,unsigned char*) ; 

__attribute__((used)) static inline void br_set_ticks(unsigned char *dest, int j)
{
	unsigned long ticks = (STP_HZ * j)/ HZ;

	put_unaligned_be16(ticks, dest);
}