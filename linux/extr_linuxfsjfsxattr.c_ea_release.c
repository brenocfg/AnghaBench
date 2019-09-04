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
struct inode {int dummy; } ;
struct ea_buffer {int flag; int /*<<< orphan*/  new_ea; int /*<<< orphan*/  mp; int /*<<< orphan*/  xattr; } ;

/* Variables and functions */
 int EA_EXTENT ; 
 int EA_MALLOC ; 
 int EA_NEW ; 
 int /*<<< orphan*/  addressDXD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbFree (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lengthDXD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_metapage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ea_release(struct inode *inode, struct ea_buffer *ea_buf)
{
	if (ea_buf->flag & EA_MALLOC)
		kfree(ea_buf->xattr);
	else if (ea_buf->flag & EA_EXTENT) {
		assert(ea_buf->mp);
		release_metapage(ea_buf->mp);

		if (ea_buf->flag & EA_NEW)
			dbFree(inode, addressDXD(&ea_buf->new_ea),
			       lengthDXD(&ea_buf->new_ea));
	}
}