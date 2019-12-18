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
typedef  char const env_set ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (char const*) ; 
 int /*<<< orphan*/  env_set_add_nolock (char const*,char const*) ; 

void
env_set_add(struct env_set *es, const char *str)
{
    ASSERT(es);
    ASSERT(str);
    env_set_add_nolock(es, str);
}