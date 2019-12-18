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
typedef  int /*<<< orphan*/  zend_fcall_info_cache ;
struct TYPE_4__ {int param_count; scalar_t__ no_separation; int /*<<< orphan*/ * retval; int /*<<< orphan*/ * params; } ;
typedef  TYPE_1__ zend_fcall_info ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_call_function (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
zval_rehash_callback(zend_fcall_info *z_cb, zend_fcall_info_cache *z_cb_cache,
    zend_string *hostname, long count) {

    zval zv, *z_ret = &zv;

    ZVAL_NULL(z_ret);

    zval z_args[2];

    ZVAL_STRINGL(&z_args[0], ZSTR_VAL(hostname), ZSTR_LEN(hostname));
    ZVAL_LONG(&z_args[1], count);

    z_cb->params = z_args;
    z_cb->retval = z_ret;
    
    z_cb->no_separation = 0;
    z_cb->param_count = 2;

    /* run cb(hostname, count) */
    zend_call_function(z_cb, z_cb_cache);

    /* cleanup */
    zval_dtor(&z_args[0]);
    zval_dtor(z_ret);
}