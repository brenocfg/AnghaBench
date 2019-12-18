#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {size_t capacity; int /*<<< orphan*/ * stack; scalar_t__ fixed; } ;
typedef  TYPE_1__ calldata_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * brealloc (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static inline bool cd_ensure_capacity(calldata_t *data, uint8_t **pos,
				      size_t new_size)
{
	size_t offset;
	size_t new_capacity;

	if (new_size < data->capacity)
		return true;
	if (data->fixed) {
		blog(LOG_ERROR, "Tried to go above fixed calldata stack size!");
		return false;
	}

	offset = *pos - data->stack;

	new_capacity = data->capacity * 2;
	if (new_capacity < new_size)
		new_capacity = new_size;

	data->stack = brealloc(data->stack, new_capacity);
	data->capacity = new_capacity;

	*pos = data->stack + offset;
	return true;
}