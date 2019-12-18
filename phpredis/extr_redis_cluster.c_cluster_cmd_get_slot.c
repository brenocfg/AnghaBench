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
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ redisCluster ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 scalar_t__ IS_ARRAY ; 
 scalar_t__ IS_DOUBLE ; 
 scalar_t__ IS_LONG ; 
 scalar_t__ IS_STRING ; 
 size_t ZSTR_LEN (int /*<<< orphan*/ *) ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_LVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 short cluster_find_slot (TYPE_1__*,char const*,unsigned short) ; 
 short cluster_hash_key (char*,size_t) ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int redis_key_prefix (int /*<<< orphan*/ ,char**,size_t*) ; 
 int /*<<< orphan*/ * zend_hash_index_find (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zval_get_string (int /*<<< orphan*/ *) ; 

__attribute__((used)) static short
cluster_cmd_get_slot(redisCluster *c, zval *z_arg)
{
    size_t key_len;
    int key_free;
    zval *z_host, *z_port;
    short slot;
    char *key;
    zend_string *zstr;

    /* If it's a string, treat it as a key.  Otherwise, look for a two
     * element array */
    if (Z_TYPE_P(z_arg) ==IS_STRING || Z_TYPE_P(z_arg) ==IS_LONG ||
       Z_TYPE_P(z_arg) ==IS_DOUBLE)
    {
        /* Allow for any scalar here */
        zstr = zval_get_string(z_arg);
        key = ZSTR_VAL(zstr);
        key_len = ZSTR_LEN(zstr);

        /* Hash it */
        key_free = redis_key_prefix(c->flags, &key, &key_len);
        slot = cluster_hash_key(key, key_len);
        zend_string_release(zstr);
        if (key_free) efree(key);
    } else if (Z_TYPE_P(z_arg) == IS_ARRAY &&
        (z_host = zend_hash_index_find(Z_ARRVAL_P(z_arg), 0)) != NULL &&
        (z_port = zend_hash_index_find(Z_ARRVAL_P(z_arg), 1)) != NULL &&
        Z_TYPE_P(z_host) == IS_STRING && Z_TYPE_P(z_port) == IS_LONG
    ) {
        /* Attempt to find this specific node by host:port */
        slot = cluster_find_slot(c,(const char *)Z_STRVAL_P(z_host),
            (unsigned short)Z_LVAL_P(z_port));

        /* Inform the caller if they've passed bad data */
        if (slot < 0) {
            php_error_docref(0, E_WARNING, "Unknown node %s:%ld",
                Z_STRVAL_P(z_host), Z_LVAL_P(z_port));
        }
    } else {
        php_error_docref(0, E_WARNING,
            "Direted commands musty be passed a key or [host,port] array");
        return -1;
    }

    return slot;
}