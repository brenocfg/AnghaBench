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
struct policydb {char*** sym_val_to_name; } ;

/* Variables and functions */

__attribute__((used)) static inline char *sym_name(struct policydb *p, unsigned int sym_num, unsigned int element_nr)
{
	return p->sym_val_to_name[sym_num][element_nr];
}