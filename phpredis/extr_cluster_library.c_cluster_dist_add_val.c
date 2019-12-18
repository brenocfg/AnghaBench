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
typedef  int /*<<< orphan*/  zval ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ redisCluster ;
struct TYPE_6__ {char* val; size_t val_len; int val_free; } ;
typedef  TYPE_2__ clusterKeyVal ;

/* Variables and functions */
 int redis_pack (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char**,size_t*) ; 

void cluster_dist_add_val(redisCluster *c, clusterKeyVal *kv, zval *z_val
                        )
{
    char *val;
    size_t val_len;
    int val_free;

    // Serialize our value
    val_free = redis_pack(c->flags, z_val, &val, &val_len);

    // Attach it to the provied keyval entry
    kv->val = val;
    kv->val_len = val_len;
    kv->val_free = val_free;
}