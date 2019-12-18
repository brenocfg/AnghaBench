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
struct rchan_buf {struct rchan_buf* padding; struct rchan* chan; int /*<<< orphan*/  start; } ;
struct rchan {int n_subbufs; int /*<<< orphan*/  kref; int /*<<< orphan*/  alloc_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int KMALLOC_MAX_SIZE ; 
 int /*<<< orphan*/  kfree (struct rchan_buf*) ; 
 struct rchan_buf* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 struct rchan_buf* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relay_alloc_buf (struct rchan_buf*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct rchan_buf *relay_create_buf(struct rchan *chan)
{
	struct rchan_buf *buf;

	if (chan->n_subbufs > KMALLOC_MAX_SIZE / sizeof(size_t *))
		return NULL;

	buf = kzalloc(sizeof(struct rchan_buf), GFP_KERNEL);
	if (!buf)
		return NULL;
	buf->padding = kmalloc_array(chan->n_subbufs, sizeof(size_t *),
				     GFP_KERNEL);
	if (!buf->padding)
		goto free_buf;

	buf->start = relay_alloc_buf(buf, &chan->alloc_size);
	if (!buf->start)
		goto free_buf;

	buf->chan = chan;
	kref_get(&buf->chan->kref);
	return buf;

free_buf:
	kfree(buf->padding);
	kfree(buf);
	return NULL;
}