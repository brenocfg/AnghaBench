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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ ci; } ;
struct qm_portal {TYPE_1__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32be (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void qm_out(struct qm_portal *p, u32 offset, u32 val)
{
	iowrite32be(val, p->addr.ci + offset);
}