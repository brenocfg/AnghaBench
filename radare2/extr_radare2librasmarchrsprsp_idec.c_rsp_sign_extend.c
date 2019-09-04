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
typedef  int st32 ;

/* Variables and functions */

__attribute__((used)) static inline st32 rsp_sign_extend(st32 x, st32 m)
{
	/* assume that bits of x above the m are already zeros
	* which is the case when called from rsp_operand_decode
	*/
	return (x ^ m) - m;
}