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
typedef  scalar_t__ SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  command (char*) ; 
 scalar_t__ connected ; 
 scalar_t__ macnum ; 
 int /*<<< orphan*/  proxy ; 

void disconnect(int argc, const char *argv[])
{
	extern SOCKET cout;
	extern int data;

	if (!connected)
		return;
	(void) command("QUIT");
	cout = 0;
	connected = 0;
	data = -1;
	if (!proxy) {
		macnum = 0;
	}
}