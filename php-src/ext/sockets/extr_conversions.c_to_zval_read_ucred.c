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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  res_context ;

/* Variables and functions */
 int /*<<< orphan*/  array_init_size (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  descriptors_ucred ; 
 int /*<<< orphan*/  to_zval_read_aggregation (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void to_zval_read_ucred(const char *data, zval *zv, res_context *ctx)
{
	array_init_size(zv, 3);

	to_zval_read_aggregation(data, zv, descriptors_ucred, ctx);
}