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
typedef  int /*<<< orphan*/  u16 ;
struct rtl8169_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IntrStatus ; 
 int /*<<< orphan*/  RTL_R16 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 rtl_get_events(struct rtl8169_private *tp)
{
	return RTL_R16(tp, IntrStatus);
}