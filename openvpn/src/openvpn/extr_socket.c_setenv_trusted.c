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
struct link_socket_info {TYPE_1__* lsa; } ;
struct env_set {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  actual; } ;

/* Variables and functions */
 int /*<<< orphan*/  SA_IP_PORT ; 
 int /*<<< orphan*/  setenv_link_socket_actual (struct env_set*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
setenv_trusted(struct env_set *es, const struct link_socket_info *info)
{
    setenv_link_socket_actual(es, "trusted", &info->lsa->actual, SA_IP_PORT);
}