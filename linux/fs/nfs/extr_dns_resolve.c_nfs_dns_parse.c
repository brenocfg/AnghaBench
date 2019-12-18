#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; scalar_t__ expiry_time; } ;
struct nfs_dns_ent {scalar_t__ addrlen; char* hostname; TYPE_1__ h; scalar_t__ namelen; int /*<<< orphan*/  addr; } ;
struct cache_detail {int /*<<< orphan*/  net; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buf1 ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_NEGATIVE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NFS_DNS_HOSTNAME_MAXLEN ; 
 int /*<<< orphan*/  cache_put (TYPE_1__*,struct cache_detail*) ; 
 scalar_t__ get_uint (char**,unsigned int*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 struct nfs_dns_ent* nfs_dns_lookup (struct cache_detail*,struct nfs_dns_ent*) ; 
 struct nfs_dns_ent* nfs_dns_update (struct cache_detail*,struct nfs_dns_ent*,struct nfs_dns_ent*) ; 
 scalar_t__ qword_get (char**,char*,int) ; 
 scalar_t__ rpc_pton (int /*<<< orphan*/ ,char*,scalar_t__,struct sockaddr*,int) ; 
 scalar_t__ seconds_since_boot () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs_dns_parse(struct cache_detail *cd, char *buf, int buflen)
{
	char buf1[NFS_DNS_HOSTNAME_MAXLEN+1];
	struct nfs_dns_ent key, *item;
	unsigned int ttl;
	ssize_t len;
	int ret = -EINVAL;

	if (buf[buflen-1] != '\n')
		goto out;
	buf[buflen-1] = '\0';

	len = qword_get(&buf, buf1, sizeof(buf1));
	if (len <= 0)
		goto out;
	key.addrlen = rpc_pton(cd->net, buf1, len,
			(struct sockaddr *)&key.addr,
			sizeof(key.addr));

	len = qword_get(&buf, buf1, sizeof(buf1));
	if (len <= 0)
		goto out;

	key.hostname = buf1;
	key.namelen = len;
	memset(&key.h, 0, sizeof(key.h));

	if (get_uint(&buf, &ttl) < 0)
		goto out;
	if (ttl == 0)
		goto out;
	key.h.expiry_time = ttl + seconds_since_boot();

	ret = -ENOMEM;
	item = nfs_dns_lookup(cd, &key);
	if (item == NULL)
		goto out;

	if (key.addrlen == 0)
		set_bit(CACHE_NEGATIVE, &key.h.flags);

	item = nfs_dns_update(cd, &key, item);
	if (item == NULL)
		goto out;

	ret = 0;
	cache_put(&item->h, cd);
out:
	return ret;
}