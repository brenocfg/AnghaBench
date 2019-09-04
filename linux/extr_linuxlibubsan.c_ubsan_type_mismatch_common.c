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
struct type_mismatch_data_common {scalar_t__ alignment; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  handle_misaligned_access (struct type_mismatch_data_common*,unsigned long) ; 
 int /*<<< orphan*/  handle_null_ptr_deref (struct type_mismatch_data_common*) ; 
 int /*<<< orphan*/  handle_object_size_mismatch (struct type_mismatch_data_common*,unsigned long) ; 

__attribute__((used)) static void ubsan_type_mismatch_common(struct type_mismatch_data_common *data,
				unsigned long ptr)
{

	if (!ptr)
		handle_null_ptr_deref(data);
	else if (data->alignment && !IS_ALIGNED(ptr, data->alignment))
		handle_misaligned_access(data, ptr);
	else
		handle_object_size_mismatch(data, ptr);
}