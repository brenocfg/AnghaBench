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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;
struct addrinfo {scalar_t__ ai_addr; int /*<<< orphan*/  ai_family; } ;
typedef  int /*<<< orphan*/  a ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 char* gai_strerror (int) ; 
 int getaddrinfo (char*,int /*<<< orphan*/ *,struct addrinfo const*,struct addrinfo**) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  v4_to_v6 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int main(void) {
	struct addrinfo *result;
	struct addrinfo *res;
	const struct addrinfo hints = { .ai_family = AF_INET };
	int error, sock;

	/* resolve the domain name into a list of addresses */
	error = getaddrinfo("www.example.com", NULL, &hints, &result);
	if (error != 0)	{
		fprintf(stderr, "error in getaddrinfo: %s\n", gai_strerror(error));
		return EXIT_FAILURE;
	}
	if((sock=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
		perror("socket");
		return EXIT_FAILURE;
	}
	struct sockaddr_in6 a = { .sin6_family = AF_INET6,
	                          .sin6_port = htons(80) };
	v4_to_v6(&((struct sockaddr_in *)result->ai_addr)->sin_addr, &a.sin6_addr);
	freeaddrinfo(result);

	if((error = connect(sock, (struct sockaddr *)&a, sizeof(a))) == -1) {
		perror("connect");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}