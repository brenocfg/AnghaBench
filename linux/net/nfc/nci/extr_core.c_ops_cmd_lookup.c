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
struct nci_driver_ops {scalar_t__ opcode; } ;
typedef  scalar_t__ __u16 ;

/* Variables and functions */

__attribute__((used)) static struct nci_driver_ops *ops_cmd_lookup(struct nci_driver_ops *ops,
					     size_t n_ops,
					     __u16 opcode)
{
	size_t i;
	struct nci_driver_ops *op;

	if (!ops || !n_ops)
		return NULL;

	for (i = 0; i < n_ops; i++) {
		op = &ops[i];
		if (op->opcode == opcode)
			return op;
	}

	return NULL;
}