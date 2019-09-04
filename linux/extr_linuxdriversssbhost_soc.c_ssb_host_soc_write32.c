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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct ssb_device {int core_index; struct ssb_bus* bus; } ;
struct ssb_bus {scalar_t__ mmio; } ;

/* Variables and functions */
 int SSB_CORE_SIZE ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ssb_host_soc_write32(struct ssb_device *dev, u16 offset, u32 value)
{
	struct ssb_bus *bus = dev->bus;

	offset += dev->core_index * SSB_CORE_SIZE;
	writel(value, bus->mmio + offset);
}