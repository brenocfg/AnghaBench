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
 int /*<<< orphan*/  DPRINTF (char*,unsigned char const*,unsigned char const*) ; 

__attribute__((used)) static int
json_parse_const(const unsigned char **ucp, const unsigned char *ue,
    const char *str, size_t len)
{
	const unsigned char *uc = *ucp;

	DPRINTF("Parse const: ", uc, *ucp);
	for (len--; uc < ue && --len;) {
		if (*uc++ == *++str)
			continue;
	}
	if (len)
		DPRINTF("Bad const: ", uc, *ucp);
	*ucp = uc;
	return len == 0;
}