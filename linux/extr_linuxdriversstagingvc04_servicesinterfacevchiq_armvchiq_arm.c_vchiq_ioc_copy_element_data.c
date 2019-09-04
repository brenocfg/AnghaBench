#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vchiq_io_copy_callback_context {size_t current_offset; scalar_t__ current_element_offset; TYPE_1__* current_element; int /*<<< orphan*/  elements_to_go; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {scalar_t__ size; scalar_t__ data; } ;

/* Variables and functions */
 size_t EFAULT ; 
 long copy_from_user (void*,scalar_t__,size_t) ; 
 size_t min (scalar_t__,size_t) ; 

__attribute__((used)) static ssize_t
vchiq_ioc_copy_element_data(
	void *context,
	void *dest,
	size_t offset,
	size_t maxsize)
{
	long res;
	size_t bytes_this_round;
	struct vchiq_io_copy_callback_context *copy_context =
		(struct vchiq_io_copy_callback_context *)context;

	if (offset != copy_context->current_offset)
		return 0;

	if (!copy_context->elements_to_go)
		return 0;

	/*
	 * Complex logic here to handle the case of 0 size elements
	 * in the middle of the array of elements.
	 *
	 * Need to skip over these 0 size elements.
	 */
	while (1) {
		bytes_this_round = min(copy_context->current_element->size -
				       copy_context->current_element_offset,
				       maxsize);

		if (bytes_this_round)
			break;

		copy_context->elements_to_go--;
		copy_context->current_element++;
		copy_context->current_element_offset = 0;

		if (!copy_context->elements_to_go)
			return 0;
	}

	res = copy_from_user(dest,
			     copy_context->current_element->data +
			     copy_context->current_element_offset,
			     bytes_this_round);

	if (res != 0)
		return -EFAULT;

	copy_context->current_element_offset += bytes_this_round;
	copy_context->current_offset += bytes_this_round;

	/*
	 * Check if done with current element, and if so advance to the next.
	 */
	if (copy_context->current_element_offset ==
	    copy_context->current_element->size) {
		copy_context->elements_to_go--;
		copy_context->current_element++;
		copy_context->current_element_offset = 0;
	}

	return bytes_this_round;
}