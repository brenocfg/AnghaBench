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
typedef  int u_int ;
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  EMSGSIZE ; 
 int /*<<< orphan*/  ENOENT ; 
 int NS_IN6ADDRSZ ; 
 int NS_INADDRSZ ; 
 int NS_INT16SZ ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ getbits (char const*,int*) ; 
 scalar_t__ getv4 (char const*,int*,int*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,char,int) ; 
 char* strchr (char const*,int) ; 

__attribute__((used)) static int
inet_cidr_pton_ipv6(const char *src, u_char *dst, size_t size)
{
	static const char xdigits_l[] = "0123456789abcdef",
				xdigits_u[] = "0123456789ABCDEF";
	u_char		tmp[NS_IN6ADDRSZ],
			   *tp,
			   *endp,
			   *colonp;
	const char *xdigits,
			   *curtok;
	int			ch,
				saw_xdigit;
	u_int		val;
	int			digits;
	int			bits;

	if (size < NS_IN6ADDRSZ)
		goto emsgsize;

	memset((tp = tmp), '\0', NS_IN6ADDRSZ);
	endp = tp + NS_IN6ADDRSZ;
	colonp = NULL;
	/* Leading :: requires some special handling. */
	if (*src == ':')
		if (*++src != ':')
			goto enoent;
	curtok = src;
	saw_xdigit = 0;
	val = 0;
	digits = 0;
	bits = -1;
	while ((ch = *src++) != '\0')
	{
		const char *pch;

		if ((pch = strchr((xdigits = xdigits_l), ch)) == NULL)
			pch = strchr((xdigits = xdigits_u), ch);
		if (pch != NULL)
		{
			val <<= 4;
			val |= (pch - xdigits);
			if (++digits > 4)
				goto enoent;
			saw_xdigit = 1;
			continue;
		}
		if (ch == ':')
		{
			curtok = src;
			if (!saw_xdigit)
			{
				if (colonp)
					goto enoent;
				colonp = tp;
				continue;
			}
			else if (*src == '\0')
				goto enoent;
			if (tp + NS_INT16SZ > endp)
				goto enoent;
			*tp++ = (u_char) (val >> 8) & 0xff;
			*tp++ = (u_char) val & 0xff;
			saw_xdigit = 0;
			digits = 0;
			val = 0;
			continue;
		}
		if (ch == '.' && ((tp + NS_INADDRSZ) <= endp) &&
			getv4(curtok, tp, &bits) > 0)
		{
			tp += NS_INADDRSZ;
			saw_xdigit = 0;
			break;				/* '\0' was seen by inet_pton4(). */
		}
		if (ch == '/' && getbits(src, &bits) > 0)
			break;
		goto enoent;
	}
	if (saw_xdigit)
	{
		if (tp + NS_INT16SZ > endp)
			goto enoent;
		*tp++ = (u_char) (val >> 8) & 0xff;
		*tp++ = (u_char) val & 0xff;
	}
	if (bits == -1)
		bits = 128;

	endp = tmp + 16;

	if (colonp != NULL)
	{
		/*
		 * Since some memmove()'s erroneously fail to handle overlapping
		 * regions, we'll do the shift by hand.
		 */
		const int	n = tp - colonp;
		int			i;

		if (tp == endp)
			goto enoent;
		for (i = 1; i <= n; i++)
		{
			endp[-i] = colonp[n - i];
			colonp[n - i] = 0;
		}
		tp = endp;
	}
	if (tp != endp)
		goto enoent;

	/*
	 * Copy out the result.
	 */
	memcpy(dst, tmp, NS_IN6ADDRSZ);

	return bits;

enoent:
	errno = ENOENT;
	return -1;

emsgsize:
	errno = EMSGSIZE;
	return -1;
}