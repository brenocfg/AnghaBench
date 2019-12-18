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
struct hostent {int h_length; char* h_name; int h_addrtype; int /*<<< orphan*/ * h_addr_list; int /*<<< orphan*/  h_aliases; } ;

/* Variables and functions */
 int /*<<< orphan*/  pc_stringfromipv4 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ *,int,char*) ; 

void printhostent(struct hostent *hp) {
	char ipbuf[16];
	pc_stringfromipv4(hp->h_addr_list[0], ipbuf);
	printf("alias: %p, len: %d, name: %s, addrlist: %p, addrtype: %d, ip: %s\n", 
		hp->h_aliases, 
		hp->h_length,
		hp->h_name,
		hp->h_addr_list,
		hp->h_addrtype,
		ipbuf
	);
}