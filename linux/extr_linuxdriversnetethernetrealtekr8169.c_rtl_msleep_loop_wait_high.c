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
struct rtl_cond {int dummy; } ;
struct rtl8169_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep ; 
 int rtl_loop_wait (struct rtl8169_private*,struct rtl_cond const*,int /*<<< orphan*/ ,unsigned int,int,int) ; 

__attribute__((used)) static bool rtl_msleep_loop_wait_high(struct rtl8169_private *tp,
				      const struct rtl_cond *c,
				      unsigned int d, int n)
{
	return rtl_loop_wait(tp, c, msleep, d, n, true);
}