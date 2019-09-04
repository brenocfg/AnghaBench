#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  s6_addr; scalar_t__* s6_addr32; } ;
struct TYPE_5__ {int /*<<< orphan*/  sin6_port; TYPE_1__ sin6_addr; } ;
struct TYPE_6__ {TYPE_2__ sin6; } ;
struct sockaddr_rxrpc {TYPE_3__ transport; } ;
struct afs_addr_list {unsigned int nr_addrs; struct sockaddr_rxrpc* addrs; } ;

/* Variables and functions */
 unsigned int AFS_MAX_ADDRESSES ; 
 int /*<<< orphan*/  EDESTADDRREQ ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct afs_addr_list* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _debug (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  _enter (char*,int,int,char const*,char) ; 
 int /*<<< orphan*/  _leave (char*,size_t) ; 
 struct afs_addr_list* afs_alloc_addrlist (unsigned int,unsigned short,unsigned short) ; 
 scalar_t__ htonl (int) ; 
 int /*<<< orphan*/  htons (unsigned int) ; 
 scalar_t__ in4_pton (char const*,int,int /*<<< orphan*/ *,int,char const**) ; 
 scalar_t__ in6_pton (char const*,int,int /*<<< orphan*/ ,int,char const**) ; 
 scalar_t__ isdigit (char const) ; 
 int /*<<< orphan*/  kfree (struct afs_addr_list*) ; 
 char* memchr (char const*,char,int) ; 

struct afs_addr_list *afs_parse_text_addrs(const char *text, size_t len,
					   char delim,
					   unsigned short service,
					   unsigned short port)
{
	struct afs_addr_list *alist;
	const char *p, *end = text + len;
	unsigned int nr = 0;

	_enter("%*.*s,%c", (int)len, (int)len, text, delim);

	if (!len)
		return ERR_PTR(-EDESTADDRREQ);

	if (delim == ':' && (memchr(text, ',', len) || !memchr(text, '.', len)))
		delim = ',';

	/* Count the addresses */
	p = text;
	do {
		if (!*p)
			return ERR_PTR(-EINVAL);
		if (*p == delim)
			continue;
		nr++;
		if (*p == '[') {
			p++;
			if (p == end)
				return ERR_PTR(-EINVAL);
			p = memchr(p, ']', end - p);
			if (!p)
				return ERR_PTR(-EINVAL);
			p++;
			if (p >= end)
				break;
		}

		p = memchr(p, delim, end - p);
		if (!p)
			break;
		p++;
	} while (p < end);

	_debug("%u/%u addresses", nr, AFS_MAX_ADDRESSES);
	if (nr > AFS_MAX_ADDRESSES)
		nr = AFS_MAX_ADDRESSES;

	alist = afs_alloc_addrlist(nr, service, port);
	if (!alist)
		return ERR_PTR(-ENOMEM);

	/* Extract the addresses */
	p = text;
	do {
		struct sockaddr_rxrpc *srx = &alist->addrs[alist->nr_addrs];
		const char *q, *stop;

		if (*p == delim) {
			p++;
			continue;
		}

		if (*p == '[') {
			p++;
			q = memchr(p, ']', end - p);
		} else {
			for (q = p; q < end; q++)
				if (*q == '+' || *q == delim)
					break;
		}

		if (in4_pton(p, q - p,
			     (u8 *)&srx->transport.sin6.sin6_addr.s6_addr32[3],
			     -1, &stop)) {
			srx->transport.sin6.sin6_addr.s6_addr32[0] = 0;
			srx->transport.sin6.sin6_addr.s6_addr32[1] = 0;
			srx->transport.sin6.sin6_addr.s6_addr32[2] = htonl(0xffff);
		} else if (in6_pton(p, q - p,
				    srx->transport.sin6.sin6_addr.s6_addr,
				    -1, &stop)) {
			/* Nothing to do */
		} else {
			goto bad_address;
		}

		if (stop != q)
			goto bad_address;

		p = q;
		if (q < end && *q == ']')
			p++;

		if (p < end) {
			if (*p == '+') {
				/* Port number specification "+1234" */
				unsigned int xport = 0;
				p++;
				if (p >= end || !isdigit(*p))
					goto bad_address;
				do {
					xport *= 10;
					xport += *p - '0';
					if (xport > 65535)
						goto bad_address;
					p++;
				} while (p < end && isdigit(*p));
				srx->transport.sin6.sin6_port = htons(xport);
			} else if (*p == delim) {
				p++;
			} else {
				goto bad_address;
			}
		}

		alist->nr_addrs++;
	} while (p < end && alist->nr_addrs < AFS_MAX_ADDRESSES);

	_leave(" = [nr %u]", alist->nr_addrs);
	return alist;

bad_address:
	kfree(alist);
	return ERR_PTR(-EINVAL);
}