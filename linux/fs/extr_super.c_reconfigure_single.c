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
struct super_block {int /*<<< orphan*/  s_root; } ;
struct fs_context {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct fs_context*) ; 
 int /*<<< orphan*/  MS_RMT_MASK ; 
 int PTR_ERR (struct fs_context*) ; 
 struct fs_context* fs_context_for_reconfigure (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int parse_monolithic_mount_data (struct fs_context*,void*) ; 
 int /*<<< orphan*/  put_fs_context (struct fs_context*) ; 
 int reconfigure_super (struct fs_context*) ; 

__attribute__((used)) static int reconfigure_single(struct super_block *s,
			      int flags, void *data)
{
	struct fs_context *fc;
	int ret;

	/* The caller really need to be passing fc down into mount_single(),
	 * then a chunk of this can be removed.  [Bollocks -- AV]
	 * Better yet, reconfiguration shouldn't happen, but rather the second
	 * mount should be rejected if the parameters are not compatible.
	 */
	fc = fs_context_for_reconfigure(s->s_root, flags, MS_RMT_MASK);
	if (IS_ERR(fc))
		return PTR_ERR(fc);

	ret = parse_monolithic_mount_data(fc, data);
	if (ret < 0)
		goto out;

	ret = reconfigure_super(fc);
out:
	put_fs_context(fc);
	return ret;
}