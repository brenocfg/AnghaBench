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
struct dst_entry {TYPE_1__* dev; } ;
struct TYPE_2__ {unsigned int mtu; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int fake_mtu(const struct dst_entry *dst)
{
	return dst->dev->mtu;
}