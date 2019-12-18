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
struct plugin_return {int dummy; } ;
struct plugin_list {int dummy; } ;
struct env_set {int dummy; } ;
struct argv {int dummy; } ;

/* Variables and functions */
 int plugin_call_ssl (struct plugin_list const*,int const,struct argv const*,struct plugin_return*,struct env_set*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
plugin_call(const struct plugin_list *pl,
            const int type,
            const struct argv *av,
            struct plugin_return *pr,
            struct env_set *es)
{
    return plugin_call_ssl(pl, type, av, pr, es, -1, NULL);
}