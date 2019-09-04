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
struct sockaddr_ll {int /*<<< orphan*/  sll_protocol; int /*<<< orphan*/  sll_ifindex; int /*<<< orphan*/  sll_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sll ;

/* Variables and functions */
 int /*<<< orphan*/  AF_PACKET ; 
 int /*<<< orphan*/  ETH_P_ALL ; 
 int /*<<< orphan*/  PF_PACKET ; 
 int SOCK_CLOEXEC ; 
 int SOCK_NONBLOCK ; 
 int SOCK_RAW ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_nametoindex (char const*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_ll*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int open_raw_sock(const char *name)
{
	struct sockaddr_ll sll;
	int sock;

	sock = socket(PF_PACKET, SOCK_RAW | SOCK_NONBLOCK | SOCK_CLOEXEC, htons(ETH_P_ALL));
	if (sock < 0) {
		printf("cannot create raw socket\n");
		return -1;
	}

	memset(&sll, 0, sizeof(sll));
	sll.sll_family = AF_PACKET;
	sll.sll_ifindex = if_nametoindex(name);
	sll.sll_protocol = htons(ETH_P_ALL);
	if (bind(sock, (struct sockaddr *)&sll, sizeof(sll)) < 0) {
		printf("bind to %s: %s\n", name, strerror(errno));
		close(sock);
		return -1;
	}

	return sock;
}