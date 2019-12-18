#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  void* zend_bool ;
struct TYPE_10__ {int count; double connect_timeout; double read_timeout; struct TYPE_10__* hosts; int /*<<< orphan*/ * continuum; int /*<<< orphan*/ * algorithm; int /*<<< orphan*/  z_dist; int /*<<< orphan*/  z_fun; struct TYPE_10__* prev; struct TYPE_10__* redis; void* pconnect; scalar_t__ auto_rehash; void* index; int /*<<< orphan*/ * z_multi_exec; } ;
typedef  TYPE_1__ RedisArray ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_ZVAL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 void* ecalloc (int,int) ; 
 int /*<<< orphan*/  efree (TYPE_1__*) ; 
 TYPE_1__* emalloc (int) ; 
 int /*<<< orphan*/  ra_init_function_table (TYPE_1__*) ; 
 int /*<<< orphan*/ * ra_load_hosts (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,long,void*) ; 
 int /*<<< orphan*/ * ra_make_continuum (TYPE_1__*,int) ; 
 int zend_hash_num_elements (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_string_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_release (TYPE_1__) ; 
 int /*<<< orphan*/  zval_dtor (TYPE_1__*) ; 

RedisArray *
ra_make_array(HashTable *hosts, zval *z_fun, zval *z_dist, HashTable *hosts_prev, zend_bool b_index, zend_bool b_pconnect, long retry_interval, zend_bool b_lazy_connect, double connect_timeout, double read_timeout, zend_bool consistent, zend_string *algorithm, zend_string *auth)
{
    int i, count;
    RedisArray *ra;

    if (!hosts || (count = zend_hash_num_elements(hosts)) == 0) return NULL;

    /* create object */
    ra = emalloc(sizeof(RedisArray));
    ra->hosts = ecalloc(count, sizeof(*ra->hosts));
    ra->redis = ecalloc(count, sizeof(*ra->redis));
    ra->count = 0;
    ra->z_multi_exec = NULL;
    ra->index = b_index;
    ra->auto_rehash = 0;
    ra->pconnect = b_pconnect;
    ra->connect_timeout = connect_timeout;
    ra->read_timeout = read_timeout;
    ra->continuum = NULL;
    ra->algorithm = NULL;

    if (ra_load_hosts(ra, hosts, auth, retry_interval, b_lazy_connect) == NULL || !ra->count) {
        for (i = 0; i < ra->count; ++i) {
            zval_dtor(&ra->redis[i]);
            zend_string_release(ra->hosts[i]);
        }
        efree(ra->redis);
        efree(ra->hosts);
        efree(ra);
        return NULL;
    }
    ra->prev = hosts_prev ? ra_make_array(hosts_prev, z_fun, z_dist, NULL, b_index, b_pconnect, retry_interval, b_lazy_connect, connect_timeout, read_timeout, consistent, algorithm, auth) : NULL;

    /* init array data structures */
    ra_init_function_table(ra);

    /* Set hash function and distribtor if provided */
    ZVAL_ZVAL(&ra->z_fun, z_fun, 1, 0);
    ZVAL_ZVAL(&ra->z_dist, z_dist, 1, 0);
    if (algorithm) ra->algorithm = zend_string_copy(algorithm);

    /* init continuum */
    if (consistent) {
        ra->continuum = ra_make_continuum(ra->hosts, ra->count);
    }

    return ra;
}