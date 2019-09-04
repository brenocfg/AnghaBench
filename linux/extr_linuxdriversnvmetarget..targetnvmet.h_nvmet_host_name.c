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
struct TYPE_2__ {int /*<<< orphan*/  cg_item; } ;
struct nvmet_host {TYPE_1__ group; } ;

/* Variables and functions */
 char* config_item_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline char *nvmet_host_name(struct nvmet_host *host)
{
	return config_item_name(&host->group.cg_item);
}