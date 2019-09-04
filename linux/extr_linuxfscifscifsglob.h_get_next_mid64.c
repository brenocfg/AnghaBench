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
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_next_mid ) (struct TCP_Server_Info*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct TCP_Server_Info*) ; 

__attribute__((used)) static inline __le64
get_next_mid64(struct TCP_Server_Info *server)
{
	return cpu_to_le64(server->ops->get_next_mid(server));
}