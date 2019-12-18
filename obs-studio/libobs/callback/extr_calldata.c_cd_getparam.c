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
struct TYPE_3__ {int /*<<< orphan*/ * stack; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ calldata_t ;

/* Variables and functions */
 size_t cd_serialize_size (int /*<<< orphan*/ **) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static bool cd_getparam(const calldata_t *data, const char *name, uint8_t **pos)
{
	size_t name_size;

	if (!data->size)
		return false;

	*pos = data->stack;

	name_size = cd_serialize_size(pos);
	while (name_size != 0) {
		const char *param_name = (const char *)*pos;
		size_t param_size;

		*pos += name_size;
		if (strcmp(param_name, name) == 0)
			return true;

		param_size = cd_serialize_size(pos);
		*pos += param_size;

		name_size = cd_serialize_size(pos);
	}

	*pos -= sizeof(size_t);
	return false;
}