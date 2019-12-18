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
struct pinginfo {scalar_t__* times; int /*<<< orphan*/  member_0; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
typedef  int /*<<< orphan*/  inaddrbuf ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  size_t __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int INET_ADDRSTRLEN ; 
 int /*<<< orphan*/  bpf_map_delete_elem (int,int /*<<< orphan*/ *) ; 
 scalar_t__ bpf_map_lookup_elem (int,int /*<<< orphan*/ *,struct pinginfo*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,size_t,size_t) ; 
 char* inet_ntop (int /*<<< orphan*/ ,struct in_addr*,char*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int get_stats(int fd, __u16 count, __u32 raddr)
{
	struct pinginfo pinginfo = { 0 };
	char inaddrbuf[INET_ADDRSTRLEN];
	struct in_addr inaddr;
	__u16 i;

	inaddr.s_addr = raddr;

	printf("\nXDP RTT data:\n");

	if (bpf_map_lookup_elem(fd, &raddr, &pinginfo)) {
		perror("bpf_map_lookup elem: ");
		return 1;
	}

	for (i = 0; i < count; i++) {
		if (pinginfo.times[i] == 0)
			break;

		printf("64 bytes from %s: icmp_seq=%d ttl=64 time=%#.5f ms\n",
		       inet_ntop(AF_INET, &inaddr, inaddrbuf,
				 sizeof(inaddrbuf)),
		       count + i + 1,
		       (double)pinginfo.times[i]/1000000);
	}

	if (i < count) {
		fprintf(stderr, "Expected %d samples, got %d.\n", count, i);
		return 1;
	}

	bpf_map_delete_elem(fd, &raddr);

	return 0;
}