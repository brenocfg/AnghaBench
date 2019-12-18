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
struct cifs_credits {int dummy; } ;
struct TCP_Server_Info {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* add_credits ) (struct TCP_Server_Info*,struct cifs_credits const*,int const) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct TCP_Server_Info*,struct cifs_credits const*,int const) ; 

__attribute__((used)) static inline void
add_credits(struct TCP_Server_Info *server, const struct cifs_credits *credits,
	    const int optype)
{
	server->ops->add_credits(server, credits, optype);
}