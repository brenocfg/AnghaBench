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
struct rtl8169_private {int dummy; } ;

/* Variables and functions */
 int OCPDR_DATA_MASK ; 
 int OCPDR_WRITE_CMD ; 
 int /*<<< orphan*/  r8168dp_1_mdio_access (struct rtl8169_private*,int,int) ; 

__attribute__((used)) static void r8168dp_1_mdio_write(struct rtl8169_private *tp, int reg, int value)
{
	r8168dp_1_mdio_access(tp, reg,
			      OCPDR_WRITE_CMD | (value & OCPDR_DATA_MASK));
}