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
struct error_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  error_item_free (struct error_item*) ; 

__attribute__((used)) static inline void error_item_array_free(struct error_item *array, size_t num)
{
	size_t i;
	for (i = 0; i < num; i++)
		error_item_free(array + i);
}