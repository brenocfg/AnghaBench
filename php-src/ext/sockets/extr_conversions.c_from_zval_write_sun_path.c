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
typedef  int /*<<< orphan*/  zend_string ;
struct sockaddr_un {char* sun_path; } ;
typedef  int /*<<< orphan*/  ser_context ;

/* Variables and functions */
 size_t ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_from_zval_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  memcpy (char**,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  zend_tmp_string_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zval_get_tmp_string (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void from_zval_write_sun_path(const zval *path, char *sockaddr_un_c, ser_context *ctx)
{
	zend_string			*path_str, *tmp_path_str;
	struct sockaddr_un	*saddr = (struct sockaddr_un*)sockaddr_un_c;

	path_str = zval_get_tmp_string((zval *) path, &tmp_path_str);

	/* code in this file relies on the path being nul terminated, even though
	 * this is not required, at least on linux for abstract paths. It also
	 * assumes that the path is not empty */
	if (ZSTR_LEN(path_str) == 0) {
		do_from_zval_err(ctx, "%s", "the path is cannot be empty");
		zend_tmp_string_release(tmp_path_str);
		return;
	}
	if (ZSTR_LEN(path_str) >= sizeof(saddr->sun_path)) {
		do_from_zval_err(ctx, "the path is too long, the maximum permitted "
				"length is %zd", sizeof(saddr->sun_path) - 1);
		zend_tmp_string_release(tmp_path_str);
		return;
	}

	memcpy(&saddr->sun_path, ZSTR_VAL(path_str), ZSTR_LEN(path_str));
	saddr->sun_path[ZSTR_LEN(path_str)] = '\0';

	zend_tmp_string_release(tmp_path_str);
}