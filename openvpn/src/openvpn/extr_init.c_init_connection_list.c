#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ remote_random; struct connection_list* connection_list; } ;
struct context {TYPE_1__ options; } ;
struct connection_list {int current; int len; struct connection_entry** array; } ;
struct connection_entry {int dummy; } ;

/* Variables and functions */
 int get_random () ; 

__attribute__((used)) static void
init_connection_list(struct context *c)
{
    struct connection_list *l = c->options.connection_list;

    l->current = -1;
    if (c->options.remote_random)
    {
        int i;
        for (i = 0; i < l->len; ++i)
        {
            const int j = get_random() % l->len;
            if (i != j)
            {
                struct connection_entry *tmp;
                tmp = l->array[i];
                l->array[i] = l->array[j];
                l->array[j] = tmp;
            }
        }
    }
}