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
typedef  int u32 ;
struct mt7601u_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  mt7601u_burst_write_regs (struct mt7601u_dev*,int,void const*,int) ; 

void mt7601u_wr_copy(struct mt7601u_dev *dev, u32 offset,
		     const void *data, int len)
{
	WARN_ONCE(offset & 3, "unaligned write copy off:%08x", offset);
	WARN_ONCE(len & 3, "short write copy off:%08x", offset);

	mt7601u_burst_write_regs(dev, offset, data, len / 4);
}