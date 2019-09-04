#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__** master; } ;
typedef  TYPE_3__ redisCluster ;
struct TYPE_6__ {TYPE_1__* sock; } ;
struct TYPE_5__ {unsigned short port; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int REDIS_CLUSTER_SLOTS ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char const*) ; 

short cluster_find_slot(redisCluster *c, const char *host,
                               unsigned short port)
{
    int i;

    for (i = 0; i < REDIS_CLUSTER_SLOTS; i++) {
        if (c->master[i] && c->master[i]->sock &&
           c->master[i]->sock->port == port &&
           !strcasecmp(ZSTR_VAL(c->master[i]->sock->host), host))
        {
            return i;
        }
    }

    // We didn't find it
    return -1;
}