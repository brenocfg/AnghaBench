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
struct tty_struct {struct hvc_struct* driver_data; } ;
struct TYPE_2__ {scalar_t__ count; } ;
struct hvc_struct {int outbuf_size; int n_outbuf; int outbuf; int /*<<< orphan*/  lock; TYPE_1__ port; } ;

/* Variables and functions */
 int EIO ; 
 int EPIPE ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  hvc_flush (struct hvc_struct*) ; 
 int /*<<< orphan*/  hvc_kick () ; 
 int hvc_push (struct hvc_struct*) ; 
 int /*<<< orphan*/  memcpy (int,unsigned char const*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int hvc_write(struct tty_struct *tty, const unsigned char *buf, int count)
{
	struct hvc_struct *hp = tty->driver_data;
	unsigned long flags;
	int rsize, written = 0;

	/* This write was probably executed during a tty close. */
	if (!hp)
		return -EPIPE;

	/* FIXME what's this (unprotected) check for? */
	if (hp->port.count <= 0)
		return -EIO;

	while (count > 0) {
		int ret = 0;

		spin_lock_irqsave(&hp->lock, flags);

		rsize = hp->outbuf_size - hp->n_outbuf;

		if (rsize) {
			if (rsize > count)
				rsize = count;
			memcpy(hp->outbuf + hp->n_outbuf, buf, rsize);
			count -= rsize;
			buf += rsize;
			hp->n_outbuf += rsize;
			written += rsize;
		}

		if (hp->n_outbuf > 0)
			ret = hvc_push(hp);

		spin_unlock_irqrestore(&hp->lock, flags);

		if (!ret)
			break;

		if (count) {
			if (hp->n_outbuf > 0)
				hvc_flush(hp);
			cond_resched();
		}
	}

	/*
	 * Racy, but harmless, kick thread if there is still pending data.
	 */
	if (hp->n_outbuf)
		hvc_kick();

	return written;
}