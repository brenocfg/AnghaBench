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
typedef  int u64 ;

/* Variables and functions */
 int get_unaligned_be64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_be64 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gf_mulx(u8 *pad)
{
	u64 a = get_unaligned_be64(pad);
	u64 b = get_unaligned_be64(pad + 8);

	put_unaligned_be64((a << 1) | (b >> 63), pad);
	put_unaligned_be64((b << 1) ^ ((a >> 63) ? 0x87 : 0), pad + 8);
}