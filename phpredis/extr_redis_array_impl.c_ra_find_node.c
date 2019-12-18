#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  ret ;
struct TYPE_11__ {int /*<<< orphan*/  digest_size; int /*<<< orphan*/  (* hash_final ) (unsigned char*,void*) ;int /*<<< orphan*/  (* hash_update ) (void*,unsigned char const*,int) ;int /*<<< orphan*/  (* hash_init ) (void*) ;int /*<<< orphan*/  context_size; } ;
typedef  TYPE_3__ php_hash_ops ;
struct TYPE_12__ {unsigned long count; int /*<<< orphan*/ * redis; TYPE_2__* continuum; int /*<<< orphan*/ * algorithm; int /*<<< orphan*/  z_dist; } ;
struct TYPE_10__ {int nb_points; TYPE_1__* points; } ;
struct TYPE_9__ {unsigned long value; int index; } ;
typedef  TYPE_4__ RedisArray ;

/* Variables and functions */
 int /*<<< orphan*/  CRC32 (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_NULL ; 
 int /*<<< orphan*/  MIN (int,int /*<<< orphan*/ ) ; 
 int ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ZSTR_VAL (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (void*) ; 
 void* emalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned long*,unsigned char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* php_hash_fetch_ops (int /*<<< orphan*/ *,int) ; 
 int ra_call_distributor (TYPE_4__*,char const*,int) ; 
 int /*<<< orphan*/ * ra_extract_key (TYPE_4__*,char const*,int) ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 int /*<<< orphan*/  stub2 (void*,unsigned char const*,int) ; 
 int /*<<< orphan*/  stub3 (unsigned char*,void*) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ *) ; 

zval *
ra_find_node(RedisArray *ra, const char *key, int key_len, int *out_pos)
{
    int pos;
    zend_string *out;

    /* extract relevant part of the key */
    if ((out = ra_extract_key(ra, key, key_len)) == NULL) {
        return NULL;
    }

    if (Z_TYPE(ra->z_dist) == IS_NULL) {
        int i;
        unsigned long ret = 0xffffffff;
        const php_hash_ops *ops;

        /* hash */
        if (ra->algorithm && (ops = php_hash_fetch_ops(ZSTR_VAL(ra->algorithm), ZSTR_LEN(ra->algorithm))) != NULL) {
            void *ctx = emalloc(ops->context_size);
            unsigned char *digest = emalloc(ops->digest_size);

            ops->hash_init(ctx);
            ops->hash_update(ctx, (const unsigned char *)ZSTR_VAL(out), ZSTR_LEN(out));
            ops->hash_final(digest, ctx);

            memcpy(&ret, digest, MIN(sizeof(ret), ops->digest_size));
            ret %= 0xffffffff;

            efree(digest);
            efree(ctx);
        } else {
            for (i = 0; i < ZSTR_LEN(out); ++i) {
                CRC32(ret, ZSTR_VAL(out)[i]);
            }
        }

        /* get position on ring */
        if (ra->continuum) {
            int left = 0, right = ra->continuum->nb_points;
            while (left < right) {
                i = (int)((left + right) / 2);
                if (ra->continuum->points[i].value < ret) {
                    left = i + 1;
                } else {
                    right = i;
                }
            }
            if (right == ra->continuum->nb_points) {
                right = 0;
            }
            pos = ra->continuum->points[right].index;
        } else {
            pos = (int)((ret ^ 0xffffffff) * ra->count / 0xffffffff);
        }
    } else {
        pos = ra_call_distributor(ra, key, key_len);
        if (pos < 0 || pos >= ra->count) {
            zend_string_release(out);
            return NULL;
        }
    }
    zend_string_release(out);

    if(out_pos) *out_pos = pos;

    return &ra->redis[pos];
}