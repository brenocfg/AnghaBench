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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  inet ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_BINARY_REPRESENTATION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  ip_addr (int /*<<< orphan*/ *) ; 
 int ip_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_family (int /*<<< orphan*/ *) ; 
 char* pg_inet_net_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int) ; 
 char* pstrdup (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
network_out(inet *src, bool is_cidr)
{
	char		tmp[sizeof("xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:255.255.255.255/128")];
	char	   *dst;
	int			len;

	dst = pg_inet_net_ntop(ip_family(src), ip_addr(src), ip_bits(src),
						   tmp, sizeof(tmp));
	if (dst == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_BINARY_REPRESENTATION),
				 errmsg("could not format inet value: %m")));

	/* For CIDR, add /n if not present */
	if (is_cidr && strchr(tmp, '/') == NULL)
	{
		len = strlen(tmp);
		snprintf(tmp + len, sizeof(tmp) - len, "/%u", ip_bits(src));
	}

	return pstrdup(tmp);
}