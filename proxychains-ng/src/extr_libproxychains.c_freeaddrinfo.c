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
struct addrinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT () ; 
 int /*<<< orphan*/  PDEBUG (char*,void*) ; 
 int /*<<< orphan*/  proxy_freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  proxychains_resolver ; 
 int /*<<< orphan*/  true_freeaddrinfo (struct addrinfo*) ; 

void freeaddrinfo(struct addrinfo *res) {
	INIT();
	PDEBUG("freeaddrinfo %p \n", (void *) res);

	if(!proxychains_resolver)
		true_freeaddrinfo(res);
	else
		proxy_freeaddrinfo(res);
}