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
struct symsearch {int dummy; } ;
struct module {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool each_symbol_in_section(const struct symsearch *arr,
				   unsigned int arrsize,
				   struct module *owner,
				   bool (*fn)(const struct symsearch *syms,
					      struct module *owner,
					      void *data),
				   void *data)
{
	unsigned int j;

	for (j = 0; j < arrsize; j++) {
		if (fn(&arr[j], owner, data))
			return true;
	}

	return false;
}