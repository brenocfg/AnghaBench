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
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int HFA384X_DATA0_OFF ; 
 int HFA384X_DATA1_OFF ; 
 int /*<<< orphan*/  HFA384X_OUTB (char,int) ; 
 int /*<<< orphan*/  HFA384X_OUTW_DATA (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hfa384x_to_bap(struct net_device *dev, u16 bap, void *buf, int len)
{
	u16 d_off;
	__le16 *pos;

	d_off = (bap == 1) ? HFA384X_DATA1_OFF : HFA384X_DATA0_OFF;
	pos = (__le16 *) buf;

	for ( ; len > 1; len -= 2)
		HFA384X_OUTW_DATA(*pos++, d_off);

	if (len & 1)
		HFA384X_OUTB(*((char *) pos), d_off);

	return 0;
}