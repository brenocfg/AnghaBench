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
struct hostent {char* h_name; char** h_addr_list; char** h_aliases; int h_length; int /*<<< orphan*/  h_addrtype; } ;
typedef  int socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INIT () ; 
 int /*<<< orphan*/  PDEBUG (char*,...) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,int) ; 
 int /*<<< orphan*/  pc_stringfromipv4 (unsigned char*,char*) ; 
 int /*<<< orphan*/  proxychains_resolver ; 
 struct hostent* true_gethostbyaddr (void const*,int,int) ; 

struct hostent *gethostbyaddr(const void *addr, socklen_t len, int type) {
	INIT();
	PDEBUG("TODO: proper gethostbyaddr hook\n");

	static char buf[16];
	static char ipv4[4];
	static char *list[2];
	static char *aliases[1];
	static struct hostent he;

	if(!proxychains_resolver)
		return true_gethostbyaddr(addr, len, type);
	else {

		PDEBUG("len %u\n", len);
		if(len != 4)
			return NULL;
		he.h_name = buf;
		memcpy(ipv4, addr, 4);
		list[0] = ipv4;
		list[1] = NULL;
		he.h_addr_list = list;
		he.h_addrtype = AF_INET;
		aliases[0] = NULL;
		he.h_aliases = aliases;
		he.h_length = 4;
		pc_stringfromipv4((unsigned char *) addr, buf);
		return &he;
	}
	return NULL;
}