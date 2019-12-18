#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  op_array; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ zend_extension_persist_data ;
struct TYPE_6__ {scalar_t__ (* op_array_persist_calc ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ zend_extension ;

/* Variables and functions */
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zend_extension_op_array_persist_calc_handler(zend_extension *extension, zend_extension_persist_data *data)
{
	if (extension->op_array_persist_calc) {
		data->size += extension->op_array_persist_calc(data->op_array);
	}
}