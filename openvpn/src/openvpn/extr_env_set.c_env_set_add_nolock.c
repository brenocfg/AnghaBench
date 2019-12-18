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
struct env_set {int /*<<< orphan*/ * gc; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_env_item (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_env_item (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
env_set_add_nolock(struct env_set *es, const char *str)
{
    remove_env_item(str, es->gc == NULL, &es->list);
    add_env_item((char *)str, true, &es->list, es->gc);
}