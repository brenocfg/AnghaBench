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
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_zval_read_sockaddr_aux (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void to_zval_read_name(const char *sockaddr_p, zval *zv, res_context *ctx)
{
	void *name = (void*)*(void**)sockaddr_p;
	if (name == NULL) {
		ZVAL_NULL(zv);
	} else {
		to_zval_read_sockaddr_aux(name, zv, ctx);
	}
}