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
typedef  int /*<<< orphan*/  tmp_addr ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {scalar_t__ sin_port; TYPE_1__ sin_addr; void* sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  serv_addr ;
typedef  int /*<<< orphan*/  mapped_addr ;
typedef  int /*<<< orphan*/  filename ;

/* Variables and functions */
 void* AF_INET ; 
 int /*<<< orphan*/  BPF_ANY ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int accept (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 char* bpf_log_buf ; 
 int /*<<< orphan*/  bpf_map_update_elem (int /*<<< orphan*/ ,struct sockaddr*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 scalar_t__ getpeername (int,struct sockaddr*,int*) ; 
 scalar_t__ getsockname (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int) ; 
 int /*<<< orphan*/  inet_addr (char*) ; 
 char* inet_ntoa (TYPE_1__) ; 
 scalar_t__ listen (int,int) ; 
 scalar_t__ load_bpf_file (char*) ; 
 int /*<<< orphan*/ * map_fd ; 
 scalar_t__ memcmp (struct sockaddr*,struct sockaddr*,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr*,int /*<<< orphan*/ ,int) ; 
 int ntohs (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int socket (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main(int ac, char **argv)
{
	int serverfd, serverconnfd, clientfd;
	socklen_t sockaddr_len;
	struct sockaddr serv_addr, mapped_addr, tmp_addr;
	struct sockaddr_in *serv_addr_in, *mapped_addr_in, *tmp_addr_in;
	char filename[256];
	char *ip;

	serv_addr_in = (struct sockaddr_in *)&serv_addr;
	mapped_addr_in = (struct sockaddr_in *)&mapped_addr;
	tmp_addr_in = (struct sockaddr_in *)&tmp_addr;

	snprintf(filename, sizeof(filename), "%s_kern.o", argv[0]);

	if (load_bpf_file(filename)) {
		printf("%s", bpf_log_buf);
		return 1;
	}

	assert((serverfd = socket(AF_INET, SOCK_STREAM, 0)) > 0);
	assert((clientfd = socket(AF_INET, SOCK_STREAM, 0)) > 0);

	/* Bind server to ephemeral port on lo */
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr_in->sin_family = AF_INET;
	serv_addr_in->sin_port = 0;
	serv_addr_in->sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	assert(bind(serverfd, &serv_addr, sizeof(serv_addr)) == 0);

	sockaddr_len = sizeof(serv_addr);
	assert(getsockname(serverfd, &serv_addr, &sockaddr_len) == 0);
	ip = inet_ntoa(serv_addr_in->sin_addr);
	printf("Server bound to: %s:%d\n", ip, ntohs(serv_addr_in->sin_port));

	memset(&mapped_addr, 0, sizeof(mapped_addr));
	mapped_addr_in->sin_family = AF_INET;
	mapped_addr_in->sin_port = htons(5555);
	mapped_addr_in->sin_addr.s_addr = inet_addr("255.255.255.255");

	assert(!bpf_map_update_elem(map_fd[0], &mapped_addr, &serv_addr, BPF_ANY));

	assert(listen(serverfd, 5) == 0);

	ip = inet_ntoa(mapped_addr_in->sin_addr);
	printf("Client connecting to: %s:%d\n",
	       ip, ntohs(mapped_addr_in->sin_port));
	assert(connect(clientfd, &mapped_addr, sizeof(mapped_addr)) == 0);

	sockaddr_len = sizeof(tmp_addr);
	ip = inet_ntoa(tmp_addr_in->sin_addr);
	assert((serverconnfd = accept(serverfd, &tmp_addr, &sockaddr_len)) > 0);
	printf("Server received connection from: %s:%d\n",
	       ip, ntohs(tmp_addr_in->sin_port));

	sockaddr_len = sizeof(tmp_addr);
	assert(getpeername(clientfd, &tmp_addr, &sockaddr_len) == 0);
	ip = inet_ntoa(tmp_addr_in->sin_addr);
	printf("Client's peer address: %s:%d\n",
	       ip, ntohs(tmp_addr_in->sin_port));

	/* Is the server's getsockname = the socket getpeername */
	assert(memcmp(&serv_addr, &tmp_addr, sizeof(struct sockaddr_in)) == 0);

	return 0;
}