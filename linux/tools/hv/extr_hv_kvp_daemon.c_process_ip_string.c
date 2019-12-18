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
typedef  int /*<<< orphan*/  sub_str ;
typedef  int /*<<< orphan*/  str ;
typedef  int /*<<< orphan*/  addr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  DNS 131 
#define  GATEWAY 130 
 int HV_INVALIDARG ; 
 int INET6_ADDRSTRLEN ; 
#define  IPADDR 129 
 int MAX_IP_ADDR_SIZE ; 
#define  NETMASK 128 
 scalar_t__ expand_ipv6 (char*,int) ; 
 scalar_t__ is_ipv4 (char*) ; 
 int kvp_write_file (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ parse_ip_val_buffer (char*,int*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static int process_ip_string(FILE *f, char *ip_string, int type)
{
	int error = 0;
	char addr[INET6_ADDRSTRLEN];
	int i = 0;
	int j = 0;
	char str[256];
	char sub_str[13];
	int offset = 0;

	memset(addr, 0, sizeof(addr));

	while (parse_ip_val_buffer(ip_string, &offset, addr,
					(MAX_IP_ADDR_SIZE * 2))) {

		sub_str[0] = 0;
		if (is_ipv4(addr)) {
			switch (type) {
			case IPADDR:
				snprintf(str, sizeof(str), "%s", "IPADDR");
				break;
			case NETMASK:
				snprintf(str, sizeof(str), "%s", "NETMASK");
				break;
			case GATEWAY:
				snprintf(str, sizeof(str), "%s", "GATEWAY");
				break;
			case DNS:
				snprintf(str, sizeof(str), "%s", "DNS");
				break;
			}

			if (type == DNS) {
				snprintf(sub_str, sizeof(sub_str), "%d", ++i);
			} else if (type == GATEWAY && i == 0) {
				++i;
			} else {
				snprintf(sub_str, sizeof(sub_str), "%d", i++);
			}


		} else if (expand_ipv6(addr, type)) {
			switch (type) {
			case IPADDR:
				snprintf(str, sizeof(str), "%s", "IPV6ADDR");
				break;
			case NETMASK:
				snprintf(str, sizeof(str), "%s", "IPV6NETMASK");
				break;
			case GATEWAY:
				snprintf(str, sizeof(str), "%s",
					"IPV6_DEFAULTGW");
				break;
			case DNS:
				snprintf(str, sizeof(str), "%s",  "DNS");
				break;
			}

			if (type == DNS) {
				snprintf(sub_str, sizeof(sub_str), "%d", ++i);
			} else if (j == 0) {
				++j;
			} else {
				snprintf(sub_str, sizeof(sub_str), "_%d", j++);
			}
		} else {
			return  HV_INVALIDARG;
		}

		error = kvp_write_file(f, str, sub_str, addr);
		if (error)
			return error;
		memset(addr, 0, sizeof(addr));
	}

	return 0;
}