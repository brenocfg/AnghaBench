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
typedef  int u16 ;
struct rtl8169_private {int dummy; } ;
struct ephy_info {int mask; int bits; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int rtl_ephy_read (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_ephy_write (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtl_ephy_init(struct rtl8169_private *tp, const struct ephy_info *e,
			  int len)
{
	u16 w;

	while (len-- > 0) {
		w = (rtl_ephy_read(tp, e->offset) & ~e->mask) | e->bits;
		rtl_ephy_write(tp, e->offset, w);
		e++;
	}
}