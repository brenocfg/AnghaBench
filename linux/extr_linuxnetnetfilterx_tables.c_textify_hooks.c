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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char const* const*) ; 
 scalar_t__ NFPROTO_ARP ; 
 int snprintf (char*,size_t,char*,char*,char const* const) ; 

__attribute__((used)) static char *
textify_hooks(char *buf, size_t size, unsigned int mask, uint8_t nfproto)
{
	static const char *const inetbr_names[] = {
		"PREROUTING", "INPUT", "FORWARD",
		"OUTPUT", "POSTROUTING", "BROUTING",
	};
	static const char *const arp_names[] = {
		"INPUT", "FORWARD", "OUTPUT",
	};
	const char *const *names;
	unsigned int i, max;
	char *p = buf;
	bool np = false;
	int res;

	names = (nfproto == NFPROTO_ARP) ? arp_names : inetbr_names;
	max   = (nfproto == NFPROTO_ARP) ? ARRAY_SIZE(arp_names) :
	                                   ARRAY_SIZE(inetbr_names);
	*p = '\0';
	for (i = 0; i < max; ++i) {
		if (!(mask & (1 << i)))
			continue;
		res = snprintf(p, size, "%s%s", np ? "/" : "", names[i]);
		if (res > 0) {
			size -= res;
			p += res;
		}
		np = true;
	}

	return buf;
}