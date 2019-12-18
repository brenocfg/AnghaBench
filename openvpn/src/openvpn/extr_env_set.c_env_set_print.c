#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct env_set {struct env_item* list; } ;
struct env_item {struct env_item* next; int /*<<< orphan*/  string; } ;

/* Variables and functions */
 scalar_t__ check_debug_level (int) ; 
 scalar_t__ env_safe_to_print (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg (int,char*,int,int /*<<< orphan*/ ) ; 

void
env_set_print(int msglevel, const struct env_set *es)
{
    if (check_debug_level(msglevel))
    {
        const struct env_item *e;
        int i;

        if (es)
        {
            e = es->list;
            i = 0;

            while (e)
            {
                if (env_safe_to_print(e->string))
                {
                    msg(msglevel, "ENV [%d] '%s'", i, e->string);
                }
                ++i;
                e = e->next;
            }
        }
    }
}