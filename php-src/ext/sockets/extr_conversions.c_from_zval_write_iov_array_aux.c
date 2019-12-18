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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct msghdr {TYPE_1__* msg_iov; } ;
typedef  int /*<<< orphan*/  ser_context ;
struct TYPE_2__ {int /*<<< orphan*/  iov_base; int /*<<< orphan*/  iov_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  accounted_emalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_tmp_string_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zval_get_tmp_string (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void from_zval_write_iov_array_aux(zval *elem, unsigned i, void **args, ser_context *ctx)
{
	struct msghdr	*msg = args[0];
	zend_string     *str, *tmp_str;

	str = zval_get_tmp_string(elem, &tmp_str);

	msg->msg_iov[i - 1].iov_base = accounted_emalloc(ZSTR_LEN(str), ctx);
	msg->msg_iov[i - 1].iov_len = ZSTR_LEN(str);
	memcpy(msg->msg_iov[i - 1].iov_base, ZSTR_VAL(str), ZSTR_LEN(str));

	zend_tmp_string_release(tmp_str);
}