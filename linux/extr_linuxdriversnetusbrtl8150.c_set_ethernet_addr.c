#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {TYPE_1__* netdev; } ;
typedef  TYPE_2__ rtl8150_t ;
typedef  int /*<<< orphan*/  node_id ;
struct TYPE_5__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDR ; 
 int /*<<< orphan*/  get_registers (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void set_ethernet_addr(rtl8150_t * dev)
{
	u8 node_id[6];

	get_registers(dev, IDR, sizeof(node_id), node_id);
	memcpy(dev->netdev->dev_addr, node_id, sizeof(node_id));
}