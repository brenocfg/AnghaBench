#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_uint_t ;
struct TYPE_13__ {scalar_t__ buckets; } ;
struct TYPE_10__ {TYPE_4__* wc_tail; TYPE_5__* wc_head; TYPE_7__ hash; } ;
typedef  TYPE_3__ ngx_hash_combined_t ;
struct TYPE_8__ {scalar_t__ buckets; } ;
struct TYPE_12__ {TYPE_1__ hash; } ;
struct TYPE_9__ {scalar_t__ buckets; } ;
struct TYPE_11__ {TYPE_2__ hash; } ;

/* Variables and functions */
 void* ngx_hash_find (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 void* ngx_hash_find_wc_head (TYPE_5__*,int /*<<< orphan*/ *,size_t) ; 
 void* ngx_hash_find_wc_tail (TYPE_4__*,int /*<<< orphan*/ *,size_t) ; 

void *
ngx_hash_find_combined(ngx_hash_combined_t *hash, ngx_uint_t key, u_char *name,
    size_t len)
{
    void  *value;

    if (hash->hash.buckets) {
        value = ngx_hash_find(&hash->hash, key, name, len);

        if (value) {
            return value;
        }
    }

    if (len == 0) {
        return NULL;
    }

    if (hash->wc_head && hash->wc_head->hash.buckets) {
        value = ngx_hash_find_wc_head(hash->wc_head, name, len);

        if (value) {
            return value;
        }
    }

    if (hash->wc_tail && hash->wc_tail->hash.buckets) {
        value = ngx_hash_find_wc_tail(hash->wc_tail, name, len);

        if (value) {
            return value;
        }
    }

    return NULL;
}