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
struct super_block {scalar_t__ s_magic; } ;
struct socket_smack {struct smack_known* smk_out; struct smack_known* smk_in; } ;
struct socket {TYPE_1__* sk; } ;
struct smack_known {int /*<<< orphan*/  smk_known; } ;
struct inode {struct super_block* i_sb; } ;
struct TYPE_2__ {struct socket_smack* sk_security; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct socket* SOCKET_I (struct inode*) ; 
 scalar_t__ SOCKFS_MAGIC ; 
 int /*<<< orphan*/  XATTR_SMACK_IPIN ; 
 int /*<<< orphan*/  XATTR_SMACK_IPOUT ; 
 int /*<<< orphan*/  XATTR_SMACK_SUFFIX ; 
 void* kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct smack_known* smk_of_inode (struct inode*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smack_inode_getsecurity(struct inode *inode,
				   const char *name, void **buffer,
				   bool alloc)
{
	struct socket_smack *ssp;
	struct socket *sock;
	struct super_block *sbp;
	struct inode *ip = (struct inode *)inode;
	struct smack_known *isp;

	if (strcmp(name, XATTR_SMACK_SUFFIX) == 0)
		isp = smk_of_inode(inode);
	else {
		/*
		 * The rest of the Smack xattrs are only on sockets.
		 */
		sbp = ip->i_sb;
		if (sbp->s_magic != SOCKFS_MAGIC)
			return -EOPNOTSUPP;

		sock = SOCKET_I(ip);
		if (sock == NULL || sock->sk == NULL)
			return -EOPNOTSUPP;

		ssp = sock->sk->sk_security;

		if (strcmp(name, XATTR_SMACK_IPIN) == 0)
			isp = ssp->smk_in;
		else if (strcmp(name, XATTR_SMACK_IPOUT) == 0)
			isp = ssp->smk_out;
		else
			return -EOPNOTSUPP;
	}

	if (alloc) {
		*buffer = kstrdup(isp->smk_known, GFP_KERNEL);
		if (*buffer == NULL)
			return -ENOMEM;
	}

	return strlen(isp->smk_known);
}