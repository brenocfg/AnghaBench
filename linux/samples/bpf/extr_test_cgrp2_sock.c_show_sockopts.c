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
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ get_bind_to_device (int,char*,int) ; 
 unsigned int get_priority (int) ; 
 unsigned int get_somark (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,int,char*,unsigned int,unsigned int) ; 
 int socket (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int show_sockopts(int family)
{
	unsigned int mark, prio;
	char name[16];
	int sd;

	sd = socket(family, SOCK_DGRAM, 17);
	if (sd < 0) {
		perror("socket");
		return 1;
	}

	if (get_bind_to_device(sd, name, sizeof(name)) < 0)
		return 1;

	mark = get_somark(sd);
	prio = get_priority(sd);

	close(sd);

	printf("sd %d: dev %s, mark %u, priority %u\n", sd, name, mark, prio);

	return 0;
}