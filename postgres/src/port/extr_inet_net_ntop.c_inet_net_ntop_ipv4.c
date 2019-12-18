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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EMSGSIZE ; 
 int /*<<< orphan*/  SPRINTF (char*) ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static char *
inet_net_ntop_ipv4(const u_char *src, int bits, char *dst, size_t size)
{
	char	   *odst = dst;
	char	   *t;
	int			len = 4;
	int			b;

	if (bits < 0 || bits > 32)
	{
		errno = EINVAL;
		return (NULL);
	}

	/* Always format all four octets, regardless of mask length. */
	for (b = len; b > 0; b--)
	{
		if (size <= sizeof ".255")
			goto emsgsize;
		t = dst;
		if (dst != odst)
			*dst++ = '.';
		dst += SPRINTF((dst, "%u", *src++));
		size -= (size_t) (dst - t);
	}

	/* don't print masklen if 32 bits */
	if (bits != 32)
	{
		if (size <= sizeof "/32")
			goto emsgsize;
		dst += SPRINTF((dst, "/%u", bits));
	}

	return (odst);

emsgsize:
	errno = EMSGSIZE;
	return (NULL);
}