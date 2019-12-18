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
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int sin6_family; int /*<<< orphan*/  sin6_addr; void* sin6_port; } ;
struct sockaddr_in {int sin_family; int /*<<< orphan*/  sin_addr; void* sin_port; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int bind (int,struct sockaddr const*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 void* htons (unsigned short) ; 
 int inet_pton (int,char const*,void*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int socket (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bind_sock(int domain, int type, const char *ip, unsigned short port)
{
	struct sockaddr_storage addr;
	struct sockaddr_in6 *addr6;
	struct sockaddr_in *addr4;
	int sockfd = -1;
	socklen_t len;
	int err = 0;

	sockfd = socket(domain, type, 0);
	if (sockfd < 0)
		goto err;

	memset(&addr, 0, sizeof(addr));

	if (domain == AF_INET) {
		len = sizeof(struct sockaddr_in);
		addr4 = (struct sockaddr_in *)&addr;
		addr4->sin_family = domain;
		addr4->sin_port = htons(port);
		if (inet_pton(domain, ip, (void *)&addr4->sin_addr) != 1)
			goto err;
	} else if (domain == AF_INET6) {
		len = sizeof(struct sockaddr_in6);
		addr6 = (struct sockaddr_in6 *)&addr;
		addr6->sin6_family = domain;
		addr6->sin6_port = htons(port);
		if (inet_pton(domain, ip, (void *)&addr6->sin6_addr) != 1)
			goto err;
	} else {
		goto err;
	}

	if (bind(sockfd, (const struct sockaddr *)&addr, len) == -1)
		goto err;

	goto out;
err:
	err = -1;
out:
	close(sockfd);
	return err;
}