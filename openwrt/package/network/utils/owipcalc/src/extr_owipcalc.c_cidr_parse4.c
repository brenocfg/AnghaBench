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
struct in_addr {int s_addr; } ;
struct TYPE_4__ {struct in_addr v4; } ;
struct TYPE_3__ {char* v4; } ;
struct cidr {int prefix; TYPE_2__ addr; TYPE_1__ buf; int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  free (struct cidr*) ; 
 int inet_pton (int /*<<< orphan*/ ,char*,struct in_addr*) ; 
 struct cidr* malloc (int) ; 
 int /*<<< orphan*/  memset (struct in_addr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 char* strchr (char*,char) ; 
 int strlen (char const*) ; 
 int strtoul (char*,char**,int) ; 

__attribute__((used)) static struct cidr * cidr_parse4(const char *s)
{
	char *p = NULL, *r;
	struct in_addr mask;
	struct cidr *addr = malloc(sizeof(struct cidr));

	if (!addr || (strlen(s) >= sizeof(addr->buf.v4)))
		goto err;

	snprintf(addr->buf.v4, sizeof(addr->buf.v4), "%s", s);

	addr->family = AF_INET;

	if ((p = strchr(addr->buf.v4, '/')) != NULL)
	{
		*p++ = 0;

		if (strchr(p, '.') != NULL)
		{
			if (inet_pton(AF_INET, p, &mask) != 1)
				goto err;

			for (addr->prefix = 0; mask.s_addr; mask.s_addr >>= 1)
				addr->prefix += (mask.s_addr & 1);
		}
		else
		{
			addr->prefix = strtoul(p, &r, 10);

			if ((p == r) || (*r != 0) || (addr->prefix > 32))
				goto err;
		}
	}
	else
	{
		addr->prefix = 32;
	}

	if (p == addr->buf.v4+1)
		memset(&addr->addr.v4, 0, sizeof(addr->addr.v4));
	else if (inet_pton(AF_INET, addr->buf.v4, &addr->addr.v4) != 1)
		goto err;

	return addr;

err:
	if (addr)
		free(addr);

	return NULL;
}