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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  ser_context ;
struct TYPE_3__ {char* member_0; int member_1; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; } ;
typedef  TYPE_1__ field_descriptor ;

/* Variables and functions */
 int /*<<< orphan*/  from_zval_write_aggregation (int /*<<< orphan*/  const*,char*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
#define  from_zval_write_control_array 130 
#define  from_zval_write_iov_array 129 
#define  from_zval_write_name 128 

void from_zval_write_msghdr_send(const zval *container, char *msghdr_c, ser_context *ctx)
{
	static const field_descriptor descriptors[] = {
			{"name", sizeof("name"), 0, 0, from_zval_write_name, 0},
			{"iov", sizeof("iov"), 0, 0, from_zval_write_iov_array, 0},
			{"control", sizeof("control"), 0, 0, from_zval_write_control_array, 0},
			{0}
	};

	from_zval_write_aggregation(container, msghdr_c, descriptors, ctx);
}