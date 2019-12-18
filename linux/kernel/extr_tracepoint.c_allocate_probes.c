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
struct tp_probes {void* probes; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct tp_probes* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tp_probes* p ; 
 int /*<<< orphan*/  probes ; 
 int /*<<< orphan*/  struct_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void *allocate_probes(int count)
{
	struct tp_probes *p  = kmalloc(struct_size(p, probes, count),
				       GFP_KERNEL);
	return p == NULL ? NULL : p->probes;
}