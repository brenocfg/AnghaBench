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
typedef  int /*<<< orphan*/  ser_context ;

/* Variables and functions */
 int /*<<< orphan*/  descriptors_ucred ; 
 int /*<<< orphan*/  from_zval_write_aggregation (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void from_zval_write_ucred(const zval *container, char *ucred_c, ser_context *ctx)
{
	from_zval_write_aggregation(container, ucred_c, descriptors_ucred, ctx);
}