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
 int /*<<< orphan*/  descriptors_sockaddr_in ; 
 int /*<<< orphan*/  from_zval_write_aggregation (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void from_zval_write_sockaddr_in(const zval *container, char *sockaddr, ser_context *ctx)
{
	from_zval_write_aggregation(container, sockaddr, descriptors_sockaddr_in, ctx);
}