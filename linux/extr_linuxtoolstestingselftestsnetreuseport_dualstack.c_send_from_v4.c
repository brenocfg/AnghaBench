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
struct TYPE_2__ {void* s_addr; } ;
struct sockaddr_in {scalar_t__ sin_port; TYPE_1__ sin_addr; void* sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  saddr ;
typedef  int /*<<< orphan*/  daddr ;

/* Variables and functions */
 void* AF_INET ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int /*<<< orphan*/  PORT ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 scalar_t__ send (int,char*,int,int /*<<< orphan*/ ) ; 
 int socket (void*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_from_v4(int proto)
{
	struct sockaddr_in  saddr, daddr;
	int fd;

	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = 0;

	daddr.sin_family = AF_INET;
	daddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	daddr.sin_port = htons(PORT);

	fd = socket(AF_INET, proto, 0);
	if (fd < 0)
		error(1, errno, "failed to create send socket");

	if (bind(fd, (struct sockaddr *)&saddr, sizeof(saddr)))
		error(1, errno, "failed to bind send socket");

	if (connect(fd, (struct sockaddr *)&daddr, sizeof(daddr)))
		error(1, errno, "failed to connect send socket");

	if (send(fd, "a", 1, 0) < 0)
		error(1, errno, "failed to send message");

	close(fd);
}