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
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EIO ; 

__attribute__((used)) static ssize_t
copy_message_data(
	ssize_t (*copy_callback)(void *context, void *dest,
				 size_t offset, size_t maxsize),
	void *context,
	void *dest,
	size_t size)
{
	size_t pos = 0;

	while (pos < size) {
		ssize_t callback_result;
		size_t max_bytes = size - pos;

		callback_result =
			copy_callback(context, dest + pos,
				      pos, max_bytes);

		if (callback_result < 0)
			return callback_result;

		if (!callback_result)
			return -EIO;

		if (callback_result > max_bytes)
			return -EIO;

		pos += callback_result;
	}

	return size;
}