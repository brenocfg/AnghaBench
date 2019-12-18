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
struct cifs_credits {int /*<<< orphan*/  instance; scalar_t__ value; } ;
struct TCP_Server_Info {int /*<<< orphan*/  reconnect_instance; } ;

/* Variables and functions */

int
cifs_wait_mtu_credits(struct TCP_Server_Info *server, unsigned int size,
		      unsigned int *num, struct cifs_credits *credits)
{
	*num = size;
	credits->value = 0;
	credits->instance = server->reconnect_instance;
	return 0;
}