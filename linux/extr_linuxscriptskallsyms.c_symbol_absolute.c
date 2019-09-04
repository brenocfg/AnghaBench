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
struct sym_entry {int percpu_absolute; } ;

/* Variables and functions */

__attribute__((used)) static int symbol_absolute(struct sym_entry *s)
{
	return s->percpu_absolute;
}