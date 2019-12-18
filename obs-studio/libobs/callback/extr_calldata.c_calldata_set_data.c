#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {size_t size; int /*<<< orphan*/ * stack; int /*<<< orphan*/  fixed; } ;
typedef  TYPE_1__ calldata_t ;

/* Variables and functions */
 int /*<<< orphan*/  cd_copy_data (int /*<<< orphan*/ **,void const*,size_t) ; 
 int /*<<< orphan*/  cd_copy_string (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cd_ensure_capacity (TYPE_1__*,int /*<<< orphan*/ **,size_t) ; 
 scalar_t__ cd_getparam (TYPE_1__*,char const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  cd_set_first_param (TYPE_1__*,char const*,void const*,size_t) ; 
 int /*<<< orphan*/  memcpy (size_t*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int strlen (char const*) ; 

void calldata_set_data(calldata_t *data, const char *name, const void *in,
		       size_t size)
{
	uint8_t *pos = NULL;

	if (!data || !name || !*name)
		return;

	if (!data->fixed && !data->stack) {
		cd_set_first_param(data, name, in, size);
		return;
	}

	if (cd_getparam(data, name, &pos)) {
		size_t cur_size;
		memcpy(&cur_size, pos, sizeof(size_t));

		if (cur_size < size) {
			size_t offset = size - cur_size;
			size_t bytes = data->size;

			if (!cd_ensure_capacity(data, &pos, bytes + offset))
				return;
			memmove(pos + offset, pos, bytes - (pos - data->stack));
			data->size += offset;

		} else if (cur_size > size) {
			size_t offset = cur_size - size;
			size_t bytes = data->size - offset;

			memmove(pos, pos + offset, bytes - (pos - data->stack));
			data->size -= offset;
		}

		cd_copy_data(&pos, in, size);

	} else {
		size_t name_len = strlen(name) + 1;
		size_t offset = name_len + size + sizeof(size_t) * 2;
		if (!cd_ensure_capacity(data, &pos, data->size + offset))
			return;
		data->size += offset;

		cd_copy_string(&pos, name, 0);
		cd_copy_data(&pos, in, size);
		memset(pos, 0, sizeof(size_t));
	}
}