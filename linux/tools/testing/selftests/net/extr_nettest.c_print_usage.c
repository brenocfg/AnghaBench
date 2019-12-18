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

/* Variables and functions */
 int DEFAULT_PORT ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 

__attribute__((used)) static void print_usage(char *prog)
{
	printf(
	"usage: %s OPTS\n"
	"Required:\n"
	"    -r addr       remote address to connect to (client mode only)\n"
	"    -p port       port to connect to (client mode)/listen on (server mode)\n"
	"                  (default: %d)\n"
	"    -s            server mode (default: client mode)\n"
	"    -t            timeout seconds (default: none)\n"
	"\n"
	"Optional:\n"
	"    -F            Restart server loop\n"
	"    -6            IPv6 (default is IPv4)\n"
	"    -P proto      protocol for socket: icmp, ospf (default: none)\n"
	"    -D|R          datagram (D) / raw (R) socket (default stream)\n"
	"    -l addr       local address to bind to\n"
	"\n"
	"    -d dev        bind socket to given device name\n"
	"    -S            use setsockopt (IP_UNICAST_IF or IP_MULTICAST_IF)\n"
	"                  to set device binding\n"
	"    -C            use cmsg and IP_PKTINFO to specify device binding\n"
	"\n"
	"    -L len        send random message of given length\n"
	"    -n num        number of times to send message\n"
	"\n"
	"    -M password   use MD5 sum protection\n"
	"    -g grp        multicast group (e.g., 239.1.1.1)\n"
	"    -i            interactive mode (default is echo and terminate)\n"
	"\n"
	"    -0 addr       Expected local address\n"
	"    -1 addr       Expected remote address\n"
	"    -2 dev        Expected device name (or index) to receive packet\n"
	"\n"
	"    -b            Bind test only.\n"
	"    -q            Be quiet. Run test without printing anything.\n"
	, prog, DEFAULT_PORT);
}