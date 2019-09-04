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
struct raw3215_info {int /*<<< orphan*/  port; int /*<<< orphan*/  tlet; int /*<<< orphan*/  empty_wait; int /*<<< orphan*/  timer; struct raw3215_info* buffer; struct raw3215_info* inbuf; } ;

/* Variables and functions */
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int RAW3215_BUFFER_SIZE ; 
 int RAW3215_INBUF_SIZE ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct raw3215_info*) ; 
 void* kzalloc (int,int) ; 
 int /*<<< orphan*/  raw3215_timeout ; 
 int /*<<< orphan*/  raw3215_wakeup ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_port_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct raw3215_info *raw3215_alloc_info(void)
{
	struct raw3215_info *info;

	info = kzalloc(sizeof(struct raw3215_info), GFP_KERNEL | GFP_DMA);
	if (!info)
		return NULL;

	info->buffer = kzalloc(RAW3215_BUFFER_SIZE, GFP_KERNEL | GFP_DMA);
	info->inbuf = kzalloc(RAW3215_INBUF_SIZE, GFP_KERNEL | GFP_DMA);
	if (!info->buffer || !info->inbuf) {
		kfree(info->inbuf);
		kfree(info->buffer);
		kfree(info);
		return NULL;
	}

	timer_setup(&info->timer, raw3215_timeout, 0);
	init_waitqueue_head(&info->empty_wait);
	tasklet_init(&info->tlet, raw3215_wakeup, (unsigned long)info);
	tty_port_init(&info->port);

	return info;
}