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
struct usb_stream_kernel {struct usb_stream* s; struct usb_stream* write_page; int /*<<< orphan*/ ** outurb; int /*<<< orphan*/ ** inurb; } ;
struct usb_stream {int /*<<< orphan*/  read_size; int /*<<< orphan*/  write_size; } ;

/* Variables and functions */
 unsigned int USB_STREAM_NURBS ; 
 int /*<<< orphan*/  free_pages_exact (struct usb_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ *) ; 

void usb_stream_free(struct usb_stream_kernel *sk)
{
	struct usb_stream *s;
	unsigned u;

	for (u = 0; u < USB_STREAM_NURBS; ++u) {
		usb_free_urb(sk->inurb[u]);
		sk->inurb[u] = NULL;
		usb_free_urb(sk->outurb[u]);
		sk->outurb[u] = NULL;
	}

	s = sk->s;
	if (!s)
		return;

	free_pages_exact(sk->write_page, s->write_size);
	sk->write_page = NULL;
	free_pages_exact(s, s->read_size);
	sk->s = NULL;
}