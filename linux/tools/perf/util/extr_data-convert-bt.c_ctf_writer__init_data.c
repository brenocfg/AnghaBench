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
struct TYPE_2__ {scalar_t__ string; int /*<<< orphan*/  u64_hex; int /*<<< orphan*/  u32_hex; int /*<<< orphan*/  u32; int /*<<< orphan*/  s32; int /*<<< orphan*/  u64; int /*<<< orphan*/  s64; } ;
struct ctf_writer {TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_INT_TYPE (int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ bt_ctf_field_type_string_create () ; 
 int /*<<< orphan*/  ctf_writer__cleanup_data (struct ctf_writer*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int ctf_writer__init_data(struct ctf_writer *cw)
{
#define CREATE_INT_TYPE(type, size, sign, hex)		\
do {							\
	(type) = create_int_type(size, sign, hex);	\
	if (!(type))					\
		goto err;				\
} while (0)

	CREATE_INT_TYPE(cw->data.s64, 64, true,  false);
	CREATE_INT_TYPE(cw->data.u64, 64, false, false);
	CREATE_INT_TYPE(cw->data.s32, 32, true,  false);
	CREATE_INT_TYPE(cw->data.u32, 32, false, false);
	CREATE_INT_TYPE(cw->data.u32_hex, 32, false, true);
	CREATE_INT_TYPE(cw->data.u64_hex, 64, false, true);

	cw->data.string  = bt_ctf_field_type_string_create();
	if (cw->data.string)
		return 0;

err:
	ctf_writer__cleanup_data(cw);
	pr_err("Failed to create data types.\n");
	return -1;
}