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
typedef  int u32 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __le32 p54u_lm87_chksum(const __le32 *data, size_t length)
{
	u32 chk = 0;

	length >>= 2;
	while (length--) {
		chk ^= le32_to_cpu(*data++);
		chk = (chk >> 5) ^ (chk << 3);
	}

	return cpu_to_le32(chk);
}