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
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct hostent {int /*<<< orphan*/ * h_addr_list; } ;

/* Variables and functions */
 char* inet_ntoa (struct in_addr) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct hostent* php_network_gethostbyname (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/ * zend_string_init (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_string *php_gethostbyname(char *name)
{
	struct hostent *hp;
	struct in_addr in;
	char *address;

	hp = php_network_gethostbyname(name);

	if (!hp || !*(hp->h_addr_list)) {
		return zend_string_init(name, strlen(name), 0);
	}

	memcpy(&in.s_addr, *(hp->h_addr_list), sizeof(in.s_addr));

	address = inet_ntoa(in);
	return zend_string_init(address, strlen(address), 0);
}