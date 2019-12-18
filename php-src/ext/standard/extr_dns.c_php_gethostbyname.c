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
typedef  int /*<<< orphan*/  zend_string ;
struct in_addr {struct in_addr* s_addr; } ;
struct hostent {struct in_addr* h_addr_list; } ;

/* Variables and functions */
 char* inet_ntoa (struct in_addr) ; 
 int /*<<< orphan*/  memcpy (struct in_addr**,struct in_addr*,int) ; 
 struct hostent* php_network_gethostbyname (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/ * zend_string_init (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_string *php_gethostbyname(char *name)
{
	struct hostent *hp;
	struct in_addr *h_addr_0; /* Don't call this h_addr, it's a macro! */
	struct in_addr in;
	char *address;

	hp = php_network_gethostbyname(name);
	if (!hp) {
		return zend_string_init(name, strlen(name), 0);
	}

	/* On macos h_addr_list entries may be misaligned. */
	memcpy(&h_addr_0, &hp->h_addr_list[0], sizeof(struct in_addr *));
	if (!h_addr_0) {
		return zend_string_init(name, strlen(name), 0);
	}

	memcpy(&in.s_addr, h_addr_0, sizeof(in.s_addr));

	address = inet_ntoa(in);
	return zend_string_init(address, strlen(address), 0);
}