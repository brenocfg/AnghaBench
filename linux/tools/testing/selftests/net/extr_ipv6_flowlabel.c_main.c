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
typedef  int /*<<< orphan*/  one ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  FLOWLABEL_WILDCARD ; 
 int /*<<< orphan*/  IN6ADDR_LOOPBACK_INIT ; 
 int /*<<< orphan*/  IPV6_FLOWINFO ; 
 int /*<<< orphan*/  IPV6_FL_F_CREATE ; 
 int /*<<< orphan*/  IPV6_FL_S_EXCL ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_IPV6 ; 
 scalar_t__ bind (int,void*,int) ; 
 int /*<<< orphan*/  cfg_label ; 
 scalar_t__ close (int) ; 
 scalar_t__ connect (int,void*,int) ; 
 int /*<<< orphan*/  do_recv (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_send (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  flowlabel_get (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ get_autoflowlabel_enabled () ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  parse_opts (int,char**) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
	struct sockaddr_in6 addr = {
		.sin6_family = AF_INET6,
		.sin6_port = htons(8000),
		.sin6_addr = IN6ADDR_LOOPBACK_INIT,
	};
	const int one = 1;
	int fdt, fdr;

	parse_opts(argc, argv);

	fdt = socket(PF_INET6, SOCK_DGRAM, 0);
	if (fdt == -1)
		error(1, errno, "socket t");

	fdr = socket(PF_INET6, SOCK_DGRAM, 0);
	if (fdr == -1)
		error(1, errno, "socket r");

	if (connect(fdt, (void *)&addr, sizeof(addr)))
		error(1, errno, "connect");
	if (bind(fdr, (void *)&addr, sizeof(addr)))
		error(1, errno, "bind");

	flowlabel_get(fdt, cfg_label, IPV6_FL_S_EXCL, IPV6_FL_F_CREATE);

	if (setsockopt(fdr, SOL_IPV6, IPV6_FLOWINFO, &one, sizeof(one)))
		error(1, errno, "setsockopt flowinfo");

	if (get_autoflowlabel_enabled()) {
		fprintf(stderr, "send no label: recv auto flowlabel\n");
		do_send(fdt, false, 0);
		do_recv(fdr, true, FLOWLABEL_WILDCARD);
	} else {
		fprintf(stderr, "send no label: recv no label (auto off)\n");
		do_send(fdt, false, 0);
		do_recv(fdr, false, 0);
	}

	fprintf(stderr, "send label\n");
	do_send(fdt, true, cfg_label);
	do_recv(fdr, true, cfg_label);

	if (close(fdr))
		error(1, errno, "close r");
	if (close(fdt))
		error(1, errno, "close t");

	return 0;
}