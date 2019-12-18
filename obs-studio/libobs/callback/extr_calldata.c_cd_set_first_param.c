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
struct TYPE_3__ {size_t size; size_t capacity; int /*<<< orphan*/ * stack; } ;
typedef  TYPE_1__ calldata_t ;

/* Variables and functions */
 int /*<<< orphan*/ * bmalloc (size_t) ; 
 int /*<<< orphan*/  cd_copy_data (int /*<<< orphan*/ **,void const*,size_t) ; 
 int /*<<< orphan*/  cd_copy_string (int /*<<< orphan*/ **,char const*,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static inline void cd_set_first_param(calldata_t *data, const char *name,
				      const void *in, size_t size)
{
	uint8_t *pos;
	size_t capacity;
	size_t name_len = strlen(name) + 1;

	capacity = sizeof(size_t) * 3 + name_len + size;
	data->size = capacity;

	if (capacity < 128)
		capacity = 128;

	data->capacity = capacity;
	data->stack = bmalloc(capacity);

	pos = data->stack;
	cd_copy_string(&pos, name, name_len);
	cd_copy_data(&pos, in, size);
	memset(pos, 0, sizeof(size_t));
}