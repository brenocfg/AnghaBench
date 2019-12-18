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
typedef  int /*<<< orphan*/  uint8_t ;
struct calldata {size_t capacity; int fixed; scalar_t__ size; int /*<<< orphan*/ * stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  calldata_clear (struct calldata*) ; 

__attribute__((used)) static inline void calldata_init_fixed(struct calldata *data, uint8_t *stack,
				       size_t size)
{
	data->stack = stack;
	data->capacity = size;
	data->fixed = true;
	data->size = 0;
	calldata_clear(data);
}