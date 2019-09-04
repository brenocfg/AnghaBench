#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/  sock; } ;
typedef  TYPE_1__ ser_context ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_from_zval_err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 int php_set_inet_addr (struct sockaddr_in*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_tmp_string_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zval_get_tmp_string (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void from_zval_write_sin_addr(const zval *zaddr_str, char *inaddr, ser_context *ctx)
{
	int					res;
	struct sockaddr_in	saddr = {0};
	zend_string			*addr_str, *tmp_addr_str;

	addr_str = zval_get_tmp_string((zval *) zaddr_str, &tmp_addr_str);
	res = php_set_inet_addr(&saddr, ZSTR_VAL(addr_str), ctx->sock);
	if (res) {
		memcpy(inaddr, &saddr.sin_addr, sizeof saddr.sin_addr);
	} else {
		/* error already emitted, but let's emit another more relevant */
		do_from_zval_err(ctx, "could not resolve address '%s' to get an AF_INET "
				"address", ZSTR_VAL(addr_str));
	}

	zend_tmp_string_release(tmp_addr_str);
}