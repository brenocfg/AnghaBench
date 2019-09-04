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

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_BOOL (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_assoc_long (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_assoc_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  add_next_index_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atol (char*) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* estrndup (char*,int) ; 
 int /*<<< orphan*/  zval_dtor (int /*<<< orphan*/ *) ; 

void
redis_parse_client_list_response(char *response, zval *z_ret)
{
    char *p, *lpos, *kpos = NULL, *vpos = NULL, *p2, *key, *value;
    int klen = 0, done = 0, is_numeric;
    zval z_sub_result;

    /* Allocate for response and our user */
    array_init(z_ret);
    array_init(&z_sub_result);

    // Pointers for parsing
    p = response;
    lpos = response;

    /* While we've got more to parse */
    while(!done) {
        /* What character are we on */
        switch(*p) {
            /* We're done */
            case '\0':
                done = 1;
                break;
            /* \n, ' ' mean we can pull a k/v pair */
            case '\n':
            case ' ':
                /* Grab our value */
                vpos = lpos;

                /* There is some communication error or Redis bug if we don't
                   have a key and value, but check anyway. */
                if(kpos && vpos) {
                    /* Allocate, copy in our key */
                    key = estrndup(kpos, klen);

                    /* Allocate, copy in our value */
                    value = estrndup(lpos, p - lpos);

                    /* Treat numbers as numbers, strings as strings */
                    is_numeric = 1;
                    for(p2 = value; *p2; ++p2) {
                        if(*p2 < '0' || *p2 > '9') {
                            is_numeric = 0;
                            break;
                        }
                    }

                    /* Add as a long or string, depending */
                    if(is_numeric == 1) {
                        add_assoc_long(&z_sub_result, key, atol(value));
                    } else {
                        add_assoc_string(&z_sub_result, key, value);
                    }
                    efree(value);
                    // If we hit a '\n', then we can add this user to our list
                    if(*p == '\n') {
                        /* Add our user */
                        add_next_index_zval(z_ret, &z_sub_result);

                        /* If we have another user, make another one */
                        if(*(p+1) != '\0') {
                            array_init(&z_sub_result);
                        }
                    }

                    // Free our key
                    efree(key);
                } else {
                    // Something is wrong
                    zval_dtor(z_ret);
                    ZVAL_BOOL(z_ret, 0);
                    return;
                }

                /* Move forward */
                lpos = p + 1;

                break;
            /* We can pull the key and null terminate at our sep */
            case '=':
                /* Key, key length */
                kpos = lpos;
                klen = p - lpos;

                /* Move forward */
                lpos = p + 1;

                break;
        }

        /* Increment */
        p++;
    }
}