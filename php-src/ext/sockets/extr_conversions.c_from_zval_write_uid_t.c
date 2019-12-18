#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  scalar_t__ zend_long ;
typedef  scalar_t__ uid_t ;
struct TYPE_6__ {scalar_t__ has_error; } ;
struct TYPE_7__ {TYPE_1__ err; } ;
typedef  TYPE_2__ ser_context ;
typedef  int /*<<< orphan*/  ival ;

/* Variables and functions */
 int /*<<< orphan*/  do_from_zval_err (TYPE_2__*,char*,char*) ; 
 scalar_t__ from_zval_integer_common (int /*<<< orphan*/  const*,TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__*,int) ; 

__attribute__((used)) static void from_zval_write_uid_t(const zval *arr_value, char *field, ser_context *ctx)
{
	zend_long lval;
	uid_t ival;

	lval = from_zval_integer_common(arr_value, ctx);
	if (ctx->err.has_error) {
		return;
	}

	/* uid_t can be signed or unsigned (generally unsigned) */
	if ((uid_t)-1 > (uid_t)0) {
		if (sizeof(zend_long) > sizeof(uid_t) && (lval < 0 || (uid_t)lval != lval)) {
			do_from_zval_err(ctx, "%s", "given PHP integer is out of bounds "
					"for a uid_t value");
			return;
		}
	} else {
		if (sizeof(zend_long) > sizeof(uid_t) && (uid_t)lval != lval) {
			do_from_zval_err(ctx, "%s", "given PHP integer is out of bounds "
					"for a uid_t value");
			return;
		}
	}

	ival = (uid_t)lval;
	memcpy(field, &ival, sizeof(ival));
}