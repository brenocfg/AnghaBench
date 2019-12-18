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
struct link_socket_actual {int /*<<< orphan*/  dest; } ;
struct env_set {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  setenv_sockaddr (struct env_set*,char const*,int /*<<< orphan*/ *,unsigned int const) ; 

void
setenv_link_socket_actual(struct env_set *es,
                          const char *name_prefix,
                          const struct link_socket_actual *act,
                          const unsigned int flags)
{
    setenv_sockaddr(es, name_prefix, &act->dest, flags);
}