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
struct tty_struct {struct hvc_struct* driver_data; } ;
struct hvc_struct {int outbuf_size; int n_outbuf; } ;

/* Variables and functions */

__attribute__((used)) static int hvc_write_room(struct tty_struct *tty)
{
	struct hvc_struct *hp = tty->driver_data;

	if (!hp)
		return 0;

	return hp->outbuf_size - hp->n_outbuf;
}