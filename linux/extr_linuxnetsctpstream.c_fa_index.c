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
struct flex_array {int dummy; } ;

/* Variables and functions */
 void* flex_array_get (struct flex_array*,size_t) ; 

__attribute__((used)) static size_t fa_index(struct flex_array *fa, void *elem, size_t count)
{
	size_t index = 0;

	while (count--) {
		if (elem == flex_array_get(fa, index))
			break;
		index++;
	}

	return index;
}