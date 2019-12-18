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
struct env_item {char const* string; struct env_item* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  env_string_equal (char const*,char const*) ; 

const char *
env_set_get(const struct env_set *es, const char *name)
{
    const struct env_item *item = es->list;
    while (item && !env_string_equal(item->string, name))
    {
        item = item->next;
    }
    return item ? item->string : NULL;
}