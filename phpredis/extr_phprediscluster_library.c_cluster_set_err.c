#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int clusterdown; int /*<<< orphan*/ * err; } ;
typedef  TYPE_1__ redisCluster ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/ * zend_string_init (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cluster_set_err(redisCluster *c, char *err, int err_len)
{
    // Free our last error
    if (c->err != NULL) {
        zend_string_release(c->err);
        c->err = NULL;
    }
    if (err != NULL && err_len > 0) {
        c->err = zend_string_init(err, err_len, 0);
        if (err_len >= sizeof("CLUSTERDOWN") - 1 &&
            !memcmp(err, "CLUSTERDOWN", sizeof("CLUSTERDOWN") - 1)
        ) {
            c->clusterdown = 1;
        }
    }
}