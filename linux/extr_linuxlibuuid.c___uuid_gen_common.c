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
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  prandom_bytes (int*,int) ; 

__attribute__((used)) static void __uuid_gen_common(__u8 b[16])
{
	prandom_bytes(b, 16);
	/* reversion 0b10 */
	b[8] = (b[8] & 0x3F) | 0x80;
}