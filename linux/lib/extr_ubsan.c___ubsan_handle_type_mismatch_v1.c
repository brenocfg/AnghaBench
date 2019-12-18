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
struct type_mismatch_data_v1 {unsigned long log_alignment; int /*<<< orphan*/  type_check_kind; int /*<<< orphan*/  type; int /*<<< orphan*/  location; } ;
struct type_mismatch_data_common {unsigned long alignment; int /*<<< orphan*/  type_check_kind; int /*<<< orphan*/  type; int /*<<< orphan*/ * location; } ;

/* Variables and functions */
 int /*<<< orphan*/  ubsan_type_mismatch_common (struct type_mismatch_data_common*,unsigned long) ; 

void __ubsan_handle_type_mismatch_v1(struct type_mismatch_data_v1 *data,
				void *ptr)
{

	struct type_mismatch_data_common common_data = {
		.location = &data->location,
		.type = data->type,
		.alignment = 1UL << data->log_alignment,
		.type_check_kind = data->type_check_kind
	};

	ubsan_type_mismatch_common(&common_data, (unsigned long)ptr);
}