#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flag; } ;
struct jfs_inode_info {int mode2; TYPE_1__ ea; int /*<<< orphan*/  i_inline_ea; } ;
struct jfs_ea_list {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_8__ {int flag; } ;
typedef  TYPE_2__ dxd_t ;

/* Variables and functions */
 int DXD_INLINE ; 
 int /*<<< orphan*/  DXDaddress (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DXDlength (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DXDsize (TYPE_2__*,int) ; 
 int EPERM ; 
 int INLINEEA ; 
 struct jfs_inode_info* JFS_IP (struct inode*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct jfs_ea_list*,int) ; 

__attribute__((used)) static int ea_write_inline(struct inode *ip, struct jfs_ea_list *ealist,
			   int size, dxd_t * ea)
{
	struct jfs_inode_info *ji = JFS_IP(ip);

	/*
	 * Make sure we have an EA -- the NULL EA list is valid, but you
	 * can't copy it!
	 */
	if (ealist && size > sizeof (struct jfs_ea_list)) {
		assert(size <= sizeof (ji->i_inline_ea));

		/*
		 * See if the space is available or if it is already being
		 * used for an inline EA.
		 */
		if (!(ji->mode2 & INLINEEA) && !(ji->ea.flag & DXD_INLINE))
			return -EPERM;

		DXDsize(ea, size);
		DXDlength(ea, 0);
		DXDaddress(ea, 0);
		memcpy(ji->i_inline_ea, ealist, size);
		ea->flag = DXD_INLINE;
		ji->mode2 &= ~INLINEEA;
	} else {
		ea->flag = 0;
		DXDsize(ea, 0);
		DXDlength(ea, 0);
		DXDaddress(ea, 0);

		/* Free up INLINE area */
		if (ji->ea.flag & DXD_INLINE)
			ji->mode2 |= INLINEEA;
	}

	return 0;
}