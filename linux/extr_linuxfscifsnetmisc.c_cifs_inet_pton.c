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

/* Variables and functions */
 int const AF_INET ; 
 int const AF_INET6 ; 
 int /*<<< orphan*/  NOISY ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,int,int,int,char const*) ; 
 int in4_pton (char const*,int,void*,char,int /*<<< orphan*/ *) ; 
 int in6_pton (char const*,int,void*,char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cifs_inet_pton(const int address_family, const char *cp, int len, void *dst)
{
	int ret = 0;

	/* calculate length by finding first slash or NULL */
	if (address_family == AF_INET)
		ret = in4_pton(cp, len, dst, '\\', NULL);
	else if (address_family == AF_INET6)
		ret = in6_pton(cp, len, dst , '\\', NULL);

	cifs_dbg(NOISY, "address conversion returned %d for %*.*s\n",
		 ret, len, len, cp);
	if (ret > 0)
		ret = 1;
	return ret;
}