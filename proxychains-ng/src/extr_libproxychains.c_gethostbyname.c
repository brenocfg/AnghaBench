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
struct hostent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT () ; 
 int /*<<< orphan*/  PDEBUG (char*,char const*) ; 
 int /*<<< orphan*/  ghbndata ; 
 struct hostent* proxy_gethostbyname (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ proxychains_resolver ; 
 struct hostent* true_gethostbyname (char const*) ; 

struct hostent *gethostbyname(const char *name) {
	INIT();
	PDEBUG("gethostbyname: %s\n", name);

	if(proxychains_resolver)
		return proxy_gethostbyname(name, &ghbndata);
	else
		return true_gethostbyname(name);

	return NULL;
}