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
struct rchan_buf {unsigned int cpu; } ;
struct rchan {int /*<<< orphan*/  buf; int /*<<< orphan*/  is_global; TYPE_1__* cb; scalar_t__ has_base_filename; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {struct dentry* (* create_buf_file ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rchan_buf*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct dentry*) ; 
 int /*<<< orphan*/  S_IRUSR ; 
 int /*<<< orphan*/  __relay_reset (struct rchan_buf*,int) ; 
 struct rchan_buf** per_cpu_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rchan_buf* relay_create_buf (struct rchan*) ; 
 struct dentry* relay_create_buf_file (struct rchan*,struct rchan_buf*,unsigned int) ; 
 int /*<<< orphan*/  relay_destroy_buf (struct rchan_buf*) ; 
 int /*<<< orphan*/  relay_set_buf_dentry (struct rchan_buf*,struct dentry*) ; 
 struct dentry* stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rchan_buf*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct rchan_buf *relay_open_buf(struct rchan *chan, unsigned int cpu)
{
 	struct rchan_buf *buf = NULL;
	struct dentry *dentry;

 	if (chan->is_global)
		return *per_cpu_ptr(chan->buf, 0);

	buf = relay_create_buf(chan);
	if (!buf)
		return NULL;

	if (chan->has_base_filename) {
		dentry = relay_create_buf_file(chan, buf, cpu);
		if (!dentry)
			goto free_buf;
		relay_set_buf_dentry(buf, dentry);
	} else {
		/* Only retrieve global info, nothing more, nothing less */
		dentry = chan->cb->create_buf_file(NULL, NULL,
						   S_IRUSR, buf,
						   &chan->is_global);
		if (IS_ERR_OR_NULL(dentry))
			goto free_buf;
	}

 	buf->cpu = cpu;
 	__relay_reset(buf, 1);

 	if(chan->is_global) {
		*per_cpu_ptr(chan->buf, 0) = buf;
 		buf->cpu = 0;
  	}

	return buf;

free_buf:
 	relay_destroy_buf(buf);
	return NULL;
}