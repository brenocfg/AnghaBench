#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  char vfsmount ;
struct sockaddr_storage {int dummy; } ;
struct nfs_clone_mount {char* mnt_path; char* hostname; int /*<<< orphan*/ * addr; int /*<<< orphan*/  dentry; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  sb; } ;
struct nfs4_string {unsigned int len; int /*<<< orphan*/  data; } ;
struct nfs4_fs_location {unsigned int nservers; struct nfs4_string* servers; int /*<<< orphan*/  rootpath; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 char* ERR_CAST (char*) ; 
 char* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IPV6_SCOPE_DELIMITER ; 
 scalar_t__ IS_ERR (char*) ; 
 TYPE_1__* NFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (size_t const,int /*<<< orphan*/ ) ; 
 scalar_t__ memchr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,unsigned int) ; 
 char* nfs4_pathname_string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_referral_fs_type ; 
 int /*<<< orphan*/  nfs_parse_server_name (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,size_t const,struct net*) ; 
 struct net* rpc_net_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,char*) ; 
 char* vfs_submount (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,struct nfs_clone_mount*) ; 

__attribute__((used)) static struct vfsmount *try_location(struct nfs_clone_mount *mountdata,
				     char *page, char *page2,
				     const struct nfs4_fs_location *location)
{
	const size_t addr_bufsize = sizeof(struct sockaddr_storage);
	struct net *net = rpc_net_ns(NFS_SB(mountdata->sb)->client);
	struct vfsmount *mnt = ERR_PTR(-ENOENT);
	char *mnt_path;
	unsigned int maxbuflen;
	unsigned int s;

	mnt_path = nfs4_pathname_string(&location->rootpath, page2, PAGE_SIZE);
	if (IS_ERR(mnt_path))
		return ERR_CAST(mnt_path);
	mountdata->mnt_path = mnt_path;
	maxbuflen = mnt_path - 1 - page2;

	mountdata->addr = kmalloc(addr_bufsize, GFP_KERNEL);
	if (mountdata->addr == NULL)
		return ERR_PTR(-ENOMEM);

	for (s = 0; s < location->nservers; s++) {
		const struct nfs4_string *buf = &location->servers[s];

		if (buf->len <= 0 || buf->len >= maxbuflen)
			continue;

		if (memchr(buf->data, IPV6_SCOPE_DELIMITER, buf->len))
			continue;

		mountdata->addrlen = nfs_parse_server_name(buf->data, buf->len,
				mountdata->addr, addr_bufsize, net);
		if (mountdata->addrlen == 0)
			continue;

		memcpy(page2, buf->data, buf->len);
		page2[buf->len] = '\0';
		mountdata->hostname = page2;

		snprintf(page, PAGE_SIZE, "%s:%s",
				mountdata->hostname,
				mountdata->mnt_path);

		mnt = vfs_submount(mountdata->dentry, &nfs4_referral_fs_type, page, mountdata);
		if (!IS_ERR(mnt))
			break;
	}
	kfree(mountdata->addr);
	return mnt;
}