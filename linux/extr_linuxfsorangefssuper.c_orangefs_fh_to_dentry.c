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
typedef  scalar_t__ u32 ;
struct super_block {int dummy; } ;
struct orangefs_object_kref {scalar_t__ fs_id; int /*<<< orphan*/  khandle; } ;
struct fid {scalar_t__* raw; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GOSSIP_SUPER_DEBUG ; 
 int /*<<< orphan*/  ORANGEFS_khandle_from (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 struct dentry* d_obtain_alias (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  orangefs_iget (struct super_block*,struct orangefs_object_kref*) ; 

__attribute__((used)) static struct dentry *orangefs_fh_to_dentry(struct super_block *sb,
				  struct fid *fid,
				  int fh_len,
				  int fh_type)
{
	struct orangefs_object_kref refn;

	if (fh_len < 5 || fh_type > 2)
		return NULL;

	ORANGEFS_khandle_from(&(refn.khandle), fid->raw, 16);
	refn.fs_id = (u32) fid->raw[4];
	gossip_debug(GOSSIP_SUPER_DEBUG,
		     "fh_to_dentry: handle %pU, fs_id %d\n",
		     &refn.khandle,
		     refn.fs_id);

	return d_obtain_alias(orangefs_iget(sb, &refn));
}