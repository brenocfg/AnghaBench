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
typedef  char zval ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  RedisSock ;

/* Variables and functions */
 int SUCCESS ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_assoc_bool_ex (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_assoc_stringl_ex (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  add_assoc_zval_ex (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* redis_sock_read (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ redis_unpack (int /*<<< orphan*/ *,char*,int,char*) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_dtor (char*) ; 
 int /*<<< orphan*/ * zval_get_string (char*) ; 

int mbulk_resp_loop_assoc(RedisSock *redis_sock, zval *z_result,
                          long long count, void *ctx)
{
    char *line;
    int line_len,i = 0;
    zval *z_keys = ctx;

    // Loop while we've got replies
    while (count--) {
        zend_string *zstr = zval_get_string(&z_keys[i]);
        line = redis_sock_read(redis_sock, &line_len);

        if (line != NULL) {
            zval z_unpacked;
            if (redis_unpack(redis_sock, line, line_len, &z_unpacked)) {
                add_assoc_zval_ex(z_result, ZSTR_VAL(zstr), ZSTR_LEN(zstr), &z_unpacked);
            } else {
                add_assoc_stringl_ex(z_result, ZSTR_VAL(zstr), ZSTR_LEN(zstr), line, line_len);
            }
            efree(line);
        } else {
            add_assoc_bool_ex(z_result, ZSTR_VAL(zstr), ZSTR_LEN(zstr), 0);
        }

        // Clean up key context
        zend_string_release(zstr);
        zval_dtor(&z_keys[i]);

        // Move to the next key
        i++;
    }

    // Clean up our keys overall
    efree(z_keys);

    // Success!
    return SUCCESS;
}