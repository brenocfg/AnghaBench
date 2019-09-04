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
typedef  int u8 ;
struct mt7601u_dev {int dummy; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int /*<<< orphan*/  BBP_R47_F_TEMP ; 
 int /*<<< orphan*/  mt7601u_bbp_r47_get (struct mt7601u_dev*,int,int /*<<< orphan*/ ) ; 
 int mt7601u_bbp_rmw (struct mt7601u_dev*,int,int,int) ; 
 int mt7601u_bbp_rr (struct mt7601u_dev*,int) ; 
 int /*<<< orphan*/  trace_read_temp (struct mt7601u_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s8 mt7601u_read_temp(struct mt7601u_dev *dev)
{
	int i;
	u8 val;
	s8 temp;

	val = mt7601u_bbp_rmw(dev, 47, 0x7f, 0x10);

	/* Note: this rarely succeeds, temp can change even if it fails. */
	for (i = 100; i && (val & 0x10); i--)
		val = mt7601u_bbp_rr(dev, 47);

	temp = mt7601u_bbp_r47_get(dev, val, BBP_R47_F_TEMP);

	trace_read_temp(dev, temp);
	return temp;
}