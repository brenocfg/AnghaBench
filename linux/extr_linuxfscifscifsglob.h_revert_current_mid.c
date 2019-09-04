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
struct TCP_Server_Info {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* revert_current_mid ) (struct TCP_Server_Info*,unsigned int const) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct TCP_Server_Info*,unsigned int const) ; 

__attribute__((used)) static inline void
revert_current_mid(struct TCP_Server_Info *server, const unsigned int val)
{
	if (server->ops->revert_current_mid)
		server->ops->revert_current_mid(server, val);
}