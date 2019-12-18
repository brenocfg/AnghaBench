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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/ * smallfelem ;

/* Variables and functions */

__attribute__((used)) static void smallfelem_to_bin32(u8 out[32], const smallfelem in)
{
    *((u64 *)&out[0]) = in[0];
    *((u64 *)&out[8]) = in[1];
    *((u64 *)&out[16]) = in[2];
    *((u64 *)&out[24]) = in[3];
}