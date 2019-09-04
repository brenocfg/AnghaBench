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

/* Variables and functions */
 int BBP_R47_FLAG ; 
 int mt7601u_bbp_rr (struct mt7601u_dev*,int) ; 
 int /*<<< orphan*/  mt7601u_bbp_wr (struct mt7601u_dev*,int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static u8 mt7601u_bbp_r47_get(struct mt7601u_dev *dev, u8 reg, u8 flag)
{
	flag |= reg & ~BBP_R47_FLAG;
	mt7601u_bbp_wr(dev, 47, flag);
	usleep_range(500, 700);
	return mt7601u_bbp_rr(dev, 49);
}