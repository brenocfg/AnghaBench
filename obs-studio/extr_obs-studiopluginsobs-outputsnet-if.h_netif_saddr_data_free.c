#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t num; TYPE_1__* array; } ;
struct netif_saddr_data {TYPE_2__ addrs; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_free (TYPE_2__) ; 

__attribute__((used)) static inline void netif_saddr_data_free(struct netif_saddr_data *data)
{
	for (size_t i = 0; i < data->addrs.num; i++) {
		bfree(data->addrs.array[i].name);
		bfree(data->addrs.array[i].addr);
	}
	da_free(data->addrs);
}