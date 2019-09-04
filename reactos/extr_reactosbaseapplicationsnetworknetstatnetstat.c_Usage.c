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
typedef  int /*<<< orphan*/  VOID ;

/* Variables and functions */
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ) ; 

VOID Usage()
{
    _tprintf(_T("\nDisplays current TCP/IP protocol statistics and network connections.\n\n"
    "NETSTAT [-a] [-e] [-n] [-p proto] [-r] [-s] [interval]\n\n"
    "  -a            Displays all connections and listening ports.\n"
    "  -e            Displays Ethernet statistics. May be combined with -s\n"
    "                option\n"
    "  -n            Displays address and port numbers in numeric form.\n"
    "  -p proto      Shows connections for protocol 'proto' TCP or UDP.\n"
    "                If used with the -s option to display\n"
    "                per-protocol statistics, 'proto' may be TCP, UDP, or IP.\n"
    "  -r            Displays the current routing table.\n"
    "  -s            Displays per-protocol statistics. By default, Statistics are\n"
    "                shown for IP, ICMP, TCP and UDP;\n"
    "                the -p option may be used to specify a subset of the default.\n"
    " -o             Displays the process ID for each connection.\n"
    "  interval      Redisplays selected statistics every 'interval' seconds.\n"
    "                Press CTRL+C to stop redisplaying. By default netstat will\n"
    "                print the current information only once.\n"));
}