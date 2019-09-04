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
struct slim_stream_runtime {int /*<<< orphan*/  node; struct slim_device* dev; int /*<<< orphan*/  name; } ;
struct slim_device {int /*<<< orphan*/  stream_list_lock; int /*<<< orphan*/  stream_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct slim_stream_runtime* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  kfree (struct slim_stream_runtime*) ; 
 struct slim_stream_runtime* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct slim_stream_runtime *slim_stream_allocate(struct slim_device *dev,
						 const char *name)
{
	struct slim_stream_runtime *rt;

	rt = kzalloc(sizeof(*rt), GFP_KERNEL);
	if (!rt)
		return ERR_PTR(-ENOMEM);

	rt->name = kasprintf(GFP_KERNEL, "slim-%s", name);
	if (!rt->name) {
		kfree(rt);
		return ERR_PTR(-ENOMEM);
	}

	rt->dev = dev;
	spin_lock(&dev->stream_list_lock);
	list_add_tail(&rt->node, &dev->stream_list);
	spin_unlock(&dev->stream_list_lock);

	return rt;
}