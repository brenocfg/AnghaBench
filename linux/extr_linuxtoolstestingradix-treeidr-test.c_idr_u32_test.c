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
 int /*<<< orphan*/  DEFINE_IDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr ; 
 int /*<<< orphan*/  idr_init_base (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  idr_u32_test1 (int /*<<< orphan*/ *,int) ; 

void idr_u32_test(int base)
{
	DEFINE_IDR(idr);
	idr_init_base(&idr, base);
	idr_u32_test1(&idr, 10);
	idr_u32_test1(&idr, 0x7fffffff);
	idr_u32_test1(&idr, 0x80000000);
	idr_u32_test1(&idr, 0x80000001);
	idr_u32_test1(&idr, 0xffe00000);
	idr_u32_test1(&idr, 0xffffffff);
}