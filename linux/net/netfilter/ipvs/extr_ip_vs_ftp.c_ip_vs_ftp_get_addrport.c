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
union nf_inet_addr {void* ip; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ __u16 ;
typedef  void* __be32 ;
typedef  void* __be16 ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int IP_VS_FTP_EPSV ; 
 void* get_unaligned (void**) ; 
 void* htons (scalar_t__) ; 
 scalar_t__ in4_pton (char*,int,int /*<<< orphan*/ *,char,char const**) ; 
 scalar_t__ in6_pton (char*,int,int /*<<< orphan*/ *,char,char const**) ; 
 scalar_t__ isdigit (char) ; 
 scalar_t__ strncasecmp (char*,char const*,size_t) ; 

__attribute__((used)) static int ip_vs_ftp_get_addrport(char *data, char *data_limit,
				  const char *pattern, size_t plen,
				  char skip, bool ext, int mode,
				  union nf_inet_addr *addr, __be16 *port,
				  __u16 af, char **start, char **end)
{
	char *s, c;
	unsigned char p[6];
	char edelim;
	__u16 hport;
	int i = 0;

	if (data_limit - data < plen) {
		/* check if there is partial match */
		if (strncasecmp(data, pattern, data_limit - data) == 0)
			return -1;
		else
			return 0;
	}

	if (strncasecmp(data, pattern, plen) != 0) {
		return 0;
	}
	s = data + plen;
	if (skip) {
		bool found = false;

		for (;; s++) {
			if (s == data_limit)
				return -1;
			if (!found) {
				/* "(" is optional for non-extended format,
				 * so catch the start of IPv4 address
				 */
				if (!ext && isdigit(*s))
					break;
				if (*s == skip)
					found = true;
			} else if (*s != skip) {
				break;
			}
		}
	}
	/* Old IPv4-only format? */
	if (!ext) {
		p[0] = 0;
		for (data = s; ; data++) {
			if (data == data_limit)
				return -1;
			c = *data;
			if (isdigit(c)) {
				p[i] = p[i]*10 + c - '0';
			} else if (c == ',' && i < 5) {
				i++;
				p[i] = 0;
			} else {
				/* unexpected character or terminator */
				break;
			}
		}

		if (i != 5)
			return -1;

		*start = s;
		*end = data;
		addr->ip = get_unaligned((__be32 *) p);
		*port = get_unaligned((__be16 *) (p + 4));
		return 1;
	}
	if (s == data_limit)
		return -1;
	*start = s;
	edelim = *s++;
	if (edelim < 33 || edelim > 126)
		return -1;
	if (s == data_limit)
		return -1;
	if (*s == edelim) {
		/* Address family is usually missing for EPSV response */
		if (mode != IP_VS_FTP_EPSV)
			return -1;
		s++;
		if (s == data_limit)
			return -1;
		/* Then address should be missing too */
		if (*s != edelim)
			return -1;
		/* Caller can pre-set addr, if needed */
		s++;
	} else {
		const char *ep;

		/* We allow address only from same family */
		if (af == AF_INET6 && *s != '2')
			return -1;
		if (af == AF_INET && *s != '1')
			return -1;
		s++;
		if (s == data_limit)
			return -1;
		if (*s != edelim)
			return -1;
		s++;
		if (s == data_limit)
			return -1;
		if (af == AF_INET6) {
			if (in6_pton(s, data_limit - s, (u8 *)addr, edelim,
				     &ep) <= 0)
				return -1;
		} else {
			if (in4_pton(s, data_limit - s, (u8 *)addr, edelim,
				     &ep) <= 0)
				return -1;
		}
		s = (char *) ep;
		if (s == data_limit)
			return -1;
		if (*s != edelim)
			return -1;
		s++;
	}
	for (hport = 0; ; s++)
	{
		if (s == data_limit)
			return -1;
		if (!isdigit(*s))
			break;
		hport = hport * 10 + *s - '0';
	}
	if (s == data_limit || !hport || *s != edelim)
		return -1;
	s++;
	*end = s;
	*port = htons(hport);
	return 1;
}