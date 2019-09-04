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
struct mt76_dev {int rev; } ;

/* Variables and functions */

__attribute__((used)) static inline u16 mt76_rev(struct mt76_dev *dev)
{
	return dev->rev & 0xffff;
}