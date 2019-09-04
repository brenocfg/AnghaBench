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
struct raw3215_info {unsigned int line_pos; char* buffer; size_t head; int flags; int /*<<< orphan*/  cdev; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int RAW3215_BUFFER_SIZE ; 
 int RAW3215_WORKING ; 
 unsigned int TAB_STOP_SIZE ; 
 scalar_t__* _ascebc ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw3215_make_room (struct raw3215_info*,unsigned int) ; 
 int /*<<< orphan*/  raw3215_mk_write_req (struct raw3215_info*) ; 
 int /*<<< orphan*/  raw3215_try_io (struct raw3215_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void raw3215_putchar(struct raw3215_info *raw, unsigned char ch)
{
	unsigned long flags;
	unsigned int length, i;

	spin_lock_irqsave(get_ccwdev_lock(raw->cdev), flags);
	if (ch == '\t') {
		length = TAB_STOP_SIZE - (raw->line_pos%TAB_STOP_SIZE);
		raw->line_pos += length;
		ch = ' ';
	} else if (ch == '\n') {
		length = 1;
		raw->line_pos = 0;
	} else {
		length = 1;
		raw->line_pos++;
	}
	raw3215_make_room(raw, length);

	for (i = 0; i < length; i++) {
		raw->buffer[raw->head] = (char) _ascebc[(int) ch];
		raw->head = (raw->head + 1) & (RAW3215_BUFFER_SIZE - 1);
		raw->count++;
	}
	if (!(raw->flags & RAW3215_WORKING)) {
		raw3215_mk_write_req(raw);
		/* start or queue request */
		raw3215_try_io(raw);
	}
	spin_unlock_irqrestore(get_ccwdev_lock(raw->cdev), flags);
}