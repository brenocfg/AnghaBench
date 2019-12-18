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
struct ocfs2_super {int /*<<< orphan*/  osb_dx_seed; } ;
struct ocfs2_dx_hinfo {void* minor_hash; void* major_hash; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  void* __u32 ;

/* Variables and functions */
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEA_transform (void**,void**) ; 
 int /*<<< orphan*/  memcpy (void**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  str2hashbuf (char const*,int,void**,int) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,int) ; 

__attribute__((used)) static void ocfs2_dx_dir_name_hash(struct inode *dir, const char *name, int len,
				   struct ocfs2_dx_hinfo *hinfo)
{
	struct ocfs2_super *osb = OCFS2_SB(dir->i_sb);
	const char	*p;
	__u32		in[8], buf[4];

	/*
	 * XXX: Is this really necessary, if the index is never looked
	 * at by readdir? Is a hash value of '0' a bad idea?
	 */
	if ((len == 1 && !strncmp(".", name, 1)) ||
	    (len == 2 && !strncmp("..", name, 2))) {
		buf[0] = buf[1] = 0;
		goto out;
	}

#ifdef OCFS2_DEBUG_DX_DIRS
	/*
	 * This makes it very easy to debug indexing problems. We
	 * should never allow this to be selected without hand editing
	 * this file though.
	 */
	buf[0] = buf[1] = len;
	goto out;
#endif

	memcpy(buf, osb->osb_dx_seed, sizeof(buf));

	p = name;
	while (len > 0) {
		str2hashbuf(p, len, in, 4);
		TEA_transform(buf, in);
		len -= 16;
		p += 16;
	}

out:
	hinfo->major_hash = buf[0];
	hinfo->minor_hash = buf[1];
}