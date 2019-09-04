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
typedef  int /*<<< orphan*/  u8 ;
typedef  enum qeth_prot_versions { ____Placeholder_qeth_prot_versions } qeth_prot_versions ;

/* Variables and functions */
 int EINVAL ; 
 int QETH_PROT_IPV4 ; 
 scalar_t__ qeth_l3_string_to_ipaddr (char*,int,int /*<<< orphan*/ *) ; 
 int simple_strtoul (char const*,char**,int) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static int qeth_l3_parse_ipatoe(const char *buf, enum qeth_prot_versions proto,
		  u8 *addr, int *mask_bits)
{
	const char *start, *end;
	char *tmp;
	char buffer[40] = {0, };

	start = buf;
	/* get address string */
	end = strchr(start, '/');
	if (!end || (end - start >= 40)) {
		return -EINVAL;
	}
	strncpy(buffer, start, end - start);
	if (qeth_l3_string_to_ipaddr(buffer, proto, addr)) {
		return -EINVAL;
	}
	start = end + 1;
	*mask_bits = simple_strtoul(start, &tmp, 10);
	if (!strlen(start) ||
	    (tmp == start) ||
	    (*mask_bits > ((proto == QETH_PROT_IPV4) ? 32 : 128))) {
		return -EINVAL;
	}
	return 0;
}