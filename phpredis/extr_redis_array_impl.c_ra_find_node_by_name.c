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
typedef  int /*<<< orphan*/  zval ;
struct TYPE_3__ {int count; int /*<<< orphan*/ * redis; int /*<<< orphan*/ * hosts; } ;
typedef  TYPE_1__ RedisArray ;

/* Variables and functions */
 int ZSTR_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

zval *
ra_find_node_by_name(RedisArray *ra, const char *host, int host_len) {

    int i;
    for(i = 0; i < ra->count; ++i) {
        if (ZSTR_LEN(ra->hosts[i]) == host_len && strcmp(ZSTR_VAL(ra->hosts[i]), host) == 0) {
            return &ra->redis[i];
        }
    }
    return NULL;
}