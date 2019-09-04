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
struct super_block {int dummy; } ;
struct erofs_mount_private {int /*<<< orphan*/  options; int /*<<< orphan*/  dev_name; } ;

/* Variables and functions */
 int erofs_read_super (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int erofs_fill_super(struct super_block *sb,
	void *_priv, int silent)
{
	struct erofs_mount_private *priv = _priv;

	return erofs_read_super(sb, priv->dev_name,
		priv->options, silent);
}