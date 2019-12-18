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
typedef  scalar_t__ zend_uchar ;
typedef  int /*<<< orphan*/  zend_long ;

/* Variables and functions */
 scalar_t__ IS_DOUBLE ; 
 scalar_t__ IS_LONG ; 
 int /*<<< orphan*/  _NL ; 
 int /*<<< orphan*/  add_assoc_double_ex (int /*<<< orphan*/ *,char*,int,double) ; 
 int /*<<< orphan*/  add_assoc_long_ex (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_assoc_stringl_ex (int /*<<< orphan*/ *,char*,int,char*,int) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 scalar_t__ is_numeric_string (char*,int,int /*<<< orphan*/ *,double*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 char* strstr (char*,int /*<<< orphan*/ ) ; 

void
redis_parse_info_response(char *response, zval *z_ret)
{
    char *cur, *pos;

    array_init(z_ret);

    cur = response;
    while(1) {
        /* skip comments and empty lines */
        if (*cur == '#' || *cur == '\r') {
            if ((cur = strstr(cur, _NL)) == NULL) {
                break;
            }
            cur += 2;
            continue;
        }

        /* key */
        if ((pos = strchr(cur, ':')) == NULL) {
            break;
        }
        char *key = cur;
        int key_len = pos - cur;
        key[key_len] = '\0';

        /* value */
        cur = pos + 1;
        if ((pos = strstr(cur, _NL)) == NULL) {
            break;
        }
        char *value = cur;
        int value_len = pos - cur;
        value[value_len] = '\0';

        double dval;
        zend_long lval;
        zend_uchar type = is_numeric_string(value, value_len, &lval, &dval, 0);
        if (type == IS_LONG) {
            add_assoc_long_ex(z_ret, key, key_len, lval);
        } else if (type == IS_DOUBLE) {
            add_assoc_double_ex(z_ret, key, key_len, dval);
        } else {
            add_assoc_stringl_ex(z_ret, key, key_len, value, value_len);
        }

        cur = pos + 2; /* \r, \n */
    }
}