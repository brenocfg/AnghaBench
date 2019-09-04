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
struct f_midi_opts {int refcnt; int id_allocated; char* id; int /*<<< orphan*/  lock; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrndup (char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct f_midi_opts* to_f_midi_opts (struct config_item*) ; 

__attribute__((used)) static ssize_t f_midi_opts_id_store(struct config_item *item,
				    const char *page, size_t len)
{
	struct f_midi_opts *opts = to_f_midi_opts(item);
	int ret;
	char *c;

	mutex_lock(&opts->lock);
	if (opts->refcnt > 1) {
		ret = -EBUSY;
		goto end;
	}

	c = kstrndup(page, len, GFP_KERNEL);
	if (!c) {
		ret = -ENOMEM;
		goto end;
	}
	if (opts->id_allocated)
		kfree(opts->id);
	opts->id = c;
	opts->id_allocated = true;
	ret = len;
end:
	mutex_unlock(&opts->lock);
	return ret;
}