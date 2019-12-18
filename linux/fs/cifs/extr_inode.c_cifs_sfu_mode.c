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
struct tcon_link {int dummy; } ;
struct cifs_tcon {TYPE_3__* ses; } ;
struct cifs_sb_info {int dummy; } ;
struct cifs_fattr {int cf_mode; } ;
typedef  int ssize_t ;
typedef  int __u32 ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_6__ {TYPE_2__* server; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int (* query_all_EAs ) (unsigned int,struct cifs_tcon*,unsigned char const*,char*,char*,int,struct cifs_sb_info*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FYI ; 
 scalar_t__ IS_ERR (struct tcon_link*) ; 
 int PTR_ERR (struct tcon_link*) ; 
 int SFBITS_MASK ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  cifs_put_tlink (struct tcon_link*) ; 
 struct tcon_link* cifs_sb_tlink (struct cifs_sb_info*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int stub1 (unsigned int,struct cifs_tcon*,unsigned char const*,char*,char*,int,struct cifs_sb_info*) ; 
 struct cifs_tcon* tlink_tcon (struct tcon_link*) ; 

__attribute__((used)) static int cifs_sfu_mode(struct cifs_fattr *fattr, const unsigned char *path,
			 struct cifs_sb_info *cifs_sb, unsigned int xid)
{
#ifdef CONFIG_CIFS_XATTR
	ssize_t rc;
	char ea_value[4];
	__u32 mode;
	struct tcon_link *tlink;
	struct cifs_tcon *tcon;

	tlink = cifs_sb_tlink(cifs_sb);
	if (IS_ERR(tlink))
		return PTR_ERR(tlink);
	tcon = tlink_tcon(tlink);

	if (tcon->ses->server->ops->query_all_EAs == NULL) {
		cifs_put_tlink(tlink);
		return -EOPNOTSUPP;
	}

	rc = tcon->ses->server->ops->query_all_EAs(xid, tcon, path,
			"SETFILEBITS", ea_value, 4 /* size of buf */,
			cifs_sb);
	cifs_put_tlink(tlink);
	if (rc < 0)
		return (int)rc;
	else if (rc > 3) {
		mode = le32_to_cpu(*((__le32 *)ea_value));
		fattr->cf_mode &= ~SFBITS_MASK;
		cifs_dbg(FYI, "special bits 0%o org mode 0%o\n",
			 mode, fattr->cf_mode);
		fattr->cf_mode = (mode & SFBITS_MASK) | fattr->cf_mode;
		cifs_dbg(FYI, "special mode bits 0%o\n", mode);
	}

	return 0;
#else
	return -EOPNOTSUPP;
#endif
}