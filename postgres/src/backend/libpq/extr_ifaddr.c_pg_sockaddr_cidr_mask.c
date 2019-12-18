#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {int ss_family; } ;
struct TYPE_4__ {int* s6_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in6 {TYPE_2__ sin6_addr; TYPE_1__ sin_addr; } ;
struct sockaddr_in {TYPE_2__ sin6_addr; TYPE_1__ sin_addr; } ;
typedef  int /*<<< orphan*/  mask6 ;
typedef  int /*<<< orphan*/  mask4 ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  memcpy (struct sockaddr_storage*,struct sockaddr_in6*,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pg_hton32 (long) ; 
 long strtol (char*,char**,int) ; 

int
pg_sockaddr_cidr_mask(struct sockaddr_storage *mask, char *numbits, int family)
{
	long		bits;
	char	   *endptr;

	if (numbits == NULL)
	{
		bits = (family == AF_INET) ? 32 : 128;
	}
	else
	{
		bits = strtol(numbits, &endptr, 10);
		if (*numbits == '\0' || *endptr != '\0')
			return -1;
	}

	switch (family)
	{
		case AF_INET:
			{
				struct sockaddr_in mask4;
				long		maskl;

				if (bits < 0 || bits > 32)
					return -1;
				memset(&mask4, 0, sizeof(mask4));
				/* avoid "x << 32", which is not portable */
				if (bits > 0)
					maskl = (0xffffffffUL << (32 - (int) bits))
						& 0xffffffffUL;
				else
					maskl = 0;
				mask4.sin_addr.s_addr = pg_hton32(maskl);
				memcpy(mask, &mask4, sizeof(mask4));
				break;
			}

#ifdef HAVE_IPV6
		case AF_INET6:
			{
				struct sockaddr_in6 mask6;
				int			i;

				if (bits < 0 || bits > 128)
					return -1;
				memset(&mask6, 0, sizeof(mask6));
				for (i = 0; i < 16; i++)
				{
					if (bits <= 0)
						mask6.sin6_addr.s6_addr[i] = 0;
					else if (bits >= 8)
						mask6.sin6_addr.s6_addr[i] = 0xff;
					else
					{
						mask6.sin6_addr.s6_addr[i] =
							(0xff << (8 - (int) bits)) & 0xff;
					}
					bits -= 8;
				}
				memcpy(mask, &mask6, sizeof(mask6));
				break;
			}
#endif
		default:
			return -1;
	}

	mask->ss_family = family;
	return 0;
}