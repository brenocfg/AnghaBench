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
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
print_nmap_help(void)
{
    printf("Masscan (https://github.com/robertdavidgraham/masscan)\n"
"Usage: masscan [Options] -p{Target-Ports} {Target-IP-Ranges}\n"
"TARGET SPECIFICATION:\n"
"  Can pass only IPv4 address, CIDR networks, or ranges (non-nmap style)\n"
"  Ex: 10.0.0.0/8, 192.168.0.1, 10.0.0.1-10.0.0.254\n"
"  -iL <inputfilename>: Input from list of hosts/networks\n"
"  --exclude <host1[,host2][,host3],...>: Exclude hosts/networks\n"
"  --excludefile <exclude_file>: Exclude list from file\n"
"  --randomize-hosts: Randomize order of hosts (default)\n"
"HOST DISCOVERY:\n"
"  -Pn: Treat all hosts as online (default)\n"
"  -n: Never do DNS resolution (default)\n"
"SCAN TECHNIQUES:\n"
"  -sS: TCP SYN (always on, default)\n"
"SERVICE/VERSION DETECTION:\n"
"  --banners: get the banners of the listening service if available. The\n"
"    default timeout for waiting to recieve data is 30 seconds.\n"
"PORT SPECIFICATION AND SCAN ORDER:\n"
"  -p <port ranges>: Only scan specified ports\n"
"    Ex: -p22; -p1-65535; -p 111,137,80,139,8080\n"
"TIMING AND PERFORMANCE:\n"
"  --max-rate <number>: Send packets no faster than <number> per second\n"
"  --connection-timeout <number>: time in seconds a TCP connection will\n"
"    timeout while waiting for banner data from a port.\n"
"FIREWALL/IDS EVASION AND SPOOFING:\n"
"  -S/--source-ip <IP_Address>: Spoof source address\n"
"  -e <iface>: Use specified interface\n"
"  -g/--source-port <portnum>: Use given port number\n"
"  --ttl <val>: Set IP time-to-live field\n"
"  --spoof-mac <mac address/prefix/vendor name>: Spoof your MAC address\n"
"OUTPUT:\n"
"  --output-format <format>: Sets output to binary/list/unicornscan/json/ndjson/grepable/xml\n"
"  --output-file <file>: Write scan results to file. If --output-format is\n"
"     not given default is xml\n"
"  -oL/-oJ/-oD/-oG/-oB/-oX/-oU <file>: Output scan in List/JSON/nDjson/Grepable/Binary/XML/Unicornscan format,\n"
"     respectively, to the given filename. Shortcut for\n"
"     --output-format <format> --output-file <file>\n"
"  -v: Increase verbosity level (use -vv or more for greater effect)\n"
"  -d: Increase debugging level (use -dd or more for greater effect)\n"
"  --open: Only show open (or possibly open) ports\n"
"  --packet-trace: Show all packets sent and received\n"
"  --iflist: Print host interfaces and routes (for debugging)\n"
"  --append-output: Append to rather than clobber specified output files\n"
"  --resume <filename>: Resume an aborted scan\n"
"MISC:\n"
"  --send-eth: Send using raw ethernet frames (default)\n"
"  -V: Print version number\n"
"  -h: Print this help summary page.\n"
"EXAMPLES:\n"
"  masscan -v -sS 192.168.0.0/16 10.0.0.0/8 -p 80\n"
"  masscan 23.0.0.0/0 -p80 --banners -output-format binary --output-filename internet.scan\n"
"  masscan --open --banners --readscan internet.scan -oG internet_scan.grepable\n"
"SEE (https://github.com/robertdavidgraham/masscan) FOR MORE HELP\n"
"\n");
}