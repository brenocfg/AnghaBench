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
typedef  int uint64_t ;
struct stats {int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; int /*<<< orphan*/  uid; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; int /*<<< orphan*/  member_0; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  si_other ;
typedef  int /*<<< orphan*/  message ;
typedef  int /*<<< orphan*/  cookie ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PORT ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_COOKIE ; 
 int bind (int,struct sockaddr*,int) ; 
 int bpf_map_lookup_elem (int /*<<< orphan*/ ,int*,struct stats*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,...) ; 
 int getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ inet_aton (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_fd ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int recvfrom (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int sendto (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udp_client(void)
{
	struct sockaddr_in si_other = {0};
	struct sockaddr_in si_me = {0};
	struct stats dataEntry;
	int s_rcv, s_send, i, recv_len;
	char message = 'a';
	char buf;
	uint64_t cookie;
	int res;
	socklen_t cookie_len = sizeof(cookie);
	socklen_t slen = sizeof(si_other);

	s_rcv = socket(PF_INET, SOCK_DGRAM, 0);
	if (s_rcv < 0)
		error(1, errno, "rcv socket creat failed!\n");
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	if (inet_aton("127.0.0.1", &si_other.sin_addr) == 0)
		error(1, errno, "inet_aton\n");
	if (bind(s_rcv, (struct sockaddr *)&si_other, sizeof(si_other)) == -1)
		error(1, errno, "bind\n");
	s_send = socket(PF_INET, SOCK_DGRAM, 0);
	if (s_send < 0)
		error(1, errno, "send socket creat failed!\n");
	res = getsockopt(s_send, SOL_SOCKET, SO_COOKIE, &cookie, &cookie_len);
	if (res < 0)
		printf("get cookie failed: %s\n", strerror(errno));
	res = bpf_map_lookup_elem(map_fd, &cookie, &dataEntry);
	if (res != -1)
		error(1, errno, "socket stat found while flow not active\n");
	for (i = 0; i < 10; i++) {
		res = sendto(s_send, &message, sizeof(message), 0,
			     (struct sockaddr *)&si_other, slen);
		if (res == -1)
			error(1, errno, "send\n");
		if (res != sizeof(message))
			error(1, 0, "%uB != %luB\n", res, sizeof(message));
		recv_len = recvfrom(s_rcv, &buf, sizeof(buf), 0,
			     (struct sockaddr *)&si_me, &slen);
		if (recv_len < 0)
			error(1, errno, "receive\n");
		res = memcmp(&(si_other.sin_addr), &(si_me.sin_addr),
			   sizeof(si_me.sin_addr));
		if (res != 0)
			error(1, EFAULT, "sender addr error: %d\n", res);
		printf("Message received: %c\n", buf);
		res = bpf_map_lookup_elem(map_fd, &cookie, &dataEntry);
		if (res < 0)
			error(1, errno, "lookup sk stat failed, cookie: %lu\n",
			      cookie);
		printf("cookie: %lu, uid: 0x%x, Packet Count: %lu,"
			" Bytes Count: %lu\n\n", cookie, dataEntry.uid,
			dataEntry.packets, dataEntry.bytes);
	}
	close(s_send);
	close(s_rcv);
}