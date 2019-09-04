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
struct symbol {size_t end; size_t start; } ;

/* Variables and functions */

__attribute__((used)) static inline size_t symbol__size(const struct symbol *sym)
{
	return sym->end - sym->start;
}