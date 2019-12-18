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
struct TCP_Server_Info {scalar_t__ tcpStatus; } ;

/* Variables and functions */
 scalar_t__ CifsGood ; 

__attribute__((used)) static bool
cifs_can_echo(struct TCP_Server_Info *server)
{
	if (server->tcpStatus == CifsGood)
		return true;

	return false;
}