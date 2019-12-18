#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_fcall_info_cache ;
typedef  int /*<<< orphan*/  zend_fcall_info ;
struct TYPE_6__ {int /*<<< orphan*/  index; TYPE_1__* prev; } ;
struct TYPE_5__ {int count; int /*<<< orphan*/ * hosts; int /*<<< orphan*/ * redis; } ;
typedef  TYPE_2__ RedisArray ;

/* Variables and functions */
 int /*<<< orphan*/  ra_rehash_server (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
ra_rehash(RedisArray *ra, zend_fcall_info *z_cb, zend_fcall_info_cache *z_cb_cache) {
    int i;

    /* redistribute the data, server by server. */
    if(!ra->prev)
        return; /* TODO: compare the two rings for equality */

    for(i = 0; i < ra->prev->count; ++i) {
        ra_rehash_server(ra, &ra->prev->redis[i], ra->prev->hosts[i], ra->index, z_cb, z_cb_cache);
    }
}