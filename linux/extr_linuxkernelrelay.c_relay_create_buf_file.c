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
struct rchan_buf {int dummy; } ;
struct rchan {char* base_filename; int /*<<< orphan*/  is_global; int /*<<< orphan*/  parent; TYPE_1__* cb; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {struct dentry* (* create_buf_file ) (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rchan_buf*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 scalar_t__ NAME_MAX ; 
 int /*<<< orphan*/  S_IRUSR ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,scalar_t__,char*,char*,unsigned int) ; 
 struct dentry* stub1 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rchan_buf*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dentry *relay_create_buf_file(struct rchan *chan,
					    struct rchan_buf *buf,
					    unsigned int cpu)
{
	struct dentry *dentry;
	char *tmpname;

	tmpname = kzalloc(NAME_MAX + 1, GFP_KERNEL);
	if (!tmpname)
		return NULL;
	snprintf(tmpname, NAME_MAX, "%s%d", chan->base_filename, cpu);

	/* Create file in fs */
	dentry = chan->cb->create_buf_file(tmpname, chan->parent,
					   S_IRUSR, buf,
					   &chan->is_global);
	if (IS_ERR(dentry))
		dentry = NULL;

	kfree(tmpname);

	return dentry;
}