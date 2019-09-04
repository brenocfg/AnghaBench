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
struct soundscape {scalar_t__ ic_type; scalar_t__ type; int /*<<< orphan*/  lock; int /*<<< orphan*/  io_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GA_HMCTL_REG ; 
 long HOST_CTRL_IO (int /*<<< orphan*/ ) ; 
 scalar_t__ IC_ODIE ; 
 scalar_t__ IC_OPUS ; 
 scalar_t__ MEDIA_FX ; 
 long ODIE_ADDR_IO (int /*<<< orphan*/ ) ; 
 long ODIE_DATA_IO (int /*<<< orphan*/ ) ; 
 scalar_t__ SSCAPE_VIVO ; 
 int /*<<< orphan*/  activate_ad1845_unsafe (int /*<<< orphan*/ ) ; 
 int inb (long) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  outb (int,long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int sscape_read_unsafe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sscape_write_unsafe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int detect_sscape(struct soundscape *s, long wss_io)
{
	unsigned long flags;
	unsigned d;
	int retval = 0;

	spin_lock_irqsave(&s->lock, flags);

	/*
	 * The following code is lifted from the original OSS driver,
	 * and as I don't have a datasheet I cannot really comment
	 * on what it is doing...
	 */
	if ((inb(HOST_CTRL_IO(s->io_base)) & 0x78) != 0)
		goto _done;

	d = inb(ODIE_ADDR_IO(s->io_base)) & 0xf0;
	if ((d & 0x80) != 0)
		goto _done;

	if (d == 0)
		s->ic_type = IC_ODIE;
	else if ((d & 0x60) != 0)
		s->ic_type = IC_OPUS;
	else
		goto _done;

	outb(0xfa, ODIE_ADDR_IO(s->io_base));
	if ((inb(ODIE_ADDR_IO(s->io_base)) & 0x9f) != 0x0a)
		goto _done;

	outb(0xfe, ODIE_ADDR_IO(s->io_base));
	if ((inb(ODIE_ADDR_IO(s->io_base)) & 0x9f) != 0x0e)
		goto _done;

	outb(0xfe, ODIE_ADDR_IO(s->io_base));
	d = inb(ODIE_DATA_IO(s->io_base));
	if (s->type != SSCAPE_VIVO && (d & 0x9f) != 0x0e)
		goto _done;

	if (s->ic_type == IC_OPUS)
		activate_ad1845_unsafe(s->io_base);

	if (s->type == SSCAPE_VIVO)
		wss_io += 4;

	d  = sscape_read_unsafe(s->io_base, GA_HMCTL_REG);
	sscape_write_unsafe(s->io_base, GA_HMCTL_REG, d | 0xc0);

	/* wait for WSS codec */
	for (d = 0; d < 500; d++) {
		if ((inb(wss_io) & 0x80) == 0)
			break;
		spin_unlock_irqrestore(&s->lock, flags);
		msleep(1);
		spin_lock_irqsave(&s->lock, flags);
	}

	if ((inb(wss_io) & 0x80) != 0)
		goto _done;

	if (inb(wss_io + 2) == 0xff)
		goto _done;

	d  = sscape_read_unsafe(s->io_base, GA_HMCTL_REG) & 0x3f;
	sscape_write_unsafe(s->io_base, GA_HMCTL_REG, d);

	if ((inb(wss_io) & 0x80) != 0)
		s->type = MEDIA_FX;

	d = sscape_read_unsafe(s->io_base, GA_HMCTL_REG);
	sscape_write_unsafe(s->io_base, GA_HMCTL_REG, d | 0xc0);
	/* wait for WSS codec */
	for (d = 0; d < 500; d++) {
		if ((inb(wss_io) & 0x80) == 0)
			break;
		spin_unlock_irqrestore(&s->lock, flags);
		msleep(1);
		spin_lock_irqsave(&s->lock, flags);
	}

	/*
	 * SoundScape successfully detected!
	 */
	retval = 1;

_done:
	spin_unlock_irqrestore(&s->lock, flags);
	return retval;
}