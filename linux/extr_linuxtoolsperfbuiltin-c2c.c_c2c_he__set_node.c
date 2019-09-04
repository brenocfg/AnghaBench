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
struct perf_sample {scalar_t__ phys_addr; } ;
struct c2c_hist_entry {int paddr_zero; scalar_t__ paddr; int /*<<< orphan*/  paddr_cnt; int /*<<< orphan*/  nodeset; } ;
struct TYPE_2__ {int /*<<< orphan*/  mem2node; } ;

/* Variables and functions */
 scalar_t__ WARN_ONCE (int,char*) ; 
 TYPE_1__ c2c ; 
 int mem2node__node (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void c2c_he__set_node(struct c2c_hist_entry *c2c_he,
			     struct perf_sample *sample)
{
	int node;

	if (!sample->phys_addr) {
		c2c_he->paddr_zero = true;
		return;
	}

	node = mem2node__node(&c2c.mem2node, sample->phys_addr);
	if (WARN_ONCE(node < 0, "WARNING: failed to find node\n"))
		return;

	set_bit(node, c2c_he->nodeset);

	if (c2c_he->paddr != sample->phys_addr) {
		c2c_he->paddr_cnt++;
		c2c_he->paddr = sample->phys_addr;
	}
}