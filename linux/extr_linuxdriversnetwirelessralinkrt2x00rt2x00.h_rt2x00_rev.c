#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  rev; } ;
struct rt2x00_dev {TYPE_1__ chip; } ;

/* Variables and functions */

__attribute__((used)) static inline u16 rt2x00_rev(struct rt2x00_dev *rt2x00dev)
{
	return rt2x00dev->chip.rev;
}