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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * ce_be; } ;
struct qm_portal {TYPE_1__ addr; } ;

/* Variables and functions */
 int be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 qm_ce_in(struct qm_portal *p, u32 offset)
{
	return be32_to_cpu(*(p->addr.ce_be + (offset/4)));
}