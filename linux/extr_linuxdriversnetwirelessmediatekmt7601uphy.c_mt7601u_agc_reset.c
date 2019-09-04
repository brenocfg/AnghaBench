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
struct mt7601u_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt7601u_agc_default (struct mt7601u_dev*) ; 
 int /*<<< orphan*/  mt7601u_bbp_wr (struct mt7601u_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mt7601u_agc_reset(struct mt7601u_dev *dev)
{
	u8 agc = mt7601u_agc_default(dev);

	mt7601u_bbp_wr(dev, 66,	agc);
}