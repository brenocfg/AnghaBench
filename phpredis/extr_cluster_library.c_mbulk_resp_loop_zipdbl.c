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
typedef  int /*<<< orphan*/  RedisSock ;

/* Variables and functions */
 int SUCCESS ; 
 int ZSTR_LEN (int /*<<< orphan*/ *) ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_assoc_double_ex (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atof (char*) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* redis_sock_read (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ redis_unpack (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_dtor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zval_get_string (int /*<<< orphan*/ *) ; 

int mbulk_resp_loop_zipdbl(RedisSock *redis_sock, zval *z_result,
                           long long count, void *ctx)
{
    char *line, *key = NULL;
    int line_len, key_len = 0;
    long long idx = 0;

    // Our context will need to be divisible by 2
    if (count %2 != 0) {
        return -1;
    }

    // While we have elements
    while (count--) {
        line = redis_sock_read(redis_sock, &line_len);
        if (line != NULL) {
            if (idx++ % 2 == 0) {
                key = line;
                key_len = line_len;
            } else {
                zval zv, *z = &zv;
                if (redis_unpack(redis_sock,key,key_len, z)) {
                    zend_string *zstr = zval_get_string(z);
                    add_assoc_double_ex(z_result, ZSTR_VAL(zstr), ZSTR_LEN(zstr), atof(line));
                    zend_string_release(zstr);
                    zval_dtor(z);
                } else {
                    add_assoc_double_ex(z_result, key, key_len, atof(line));
                }

                /* Free our key and line */
                efree(key);
                efree(line);
            }
        }
    }

    return SUCCESS;
}