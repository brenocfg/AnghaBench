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
struct usb_stream {scalar_t__ state; unsigned int periods_polled; unsigned int periods_done; } ;
struct TYPE_2__ {struct usb_stream* s; int /*<<< orphan*/  sleep; } ;
struct us122l {unsigned int second_periods_polled; int /*<<< orphan*/  mutex; struct file* first; TYPE_1__ sk; } ;
struct snd_hwdep {struct us122l* private_data; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLWRNORM ; 
 scalar_t__ mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ usb_stream_ready ; 

__attribute__((used)) static __poll_t usb_stream_hwdep_poll(struct snd_hwdep *hw,
					  struct file *file, poll_table *wait)
{
	struct us122l	*us122l = hw->private_data;
	unsigned	*polled;
	__poll_t	mask;

	poll_wait(file, &us122l->sk.sleep, wait);

	mask = EPOLLIN | EPOLLOUT | EPOLLWRNORM | EPOLLERR;
	if (mutex_trylock(&us122l->mutex)) {
		struct usb_stream *s = us122l->sk.s;
		if (s && s->state == usb_stream_ready) {
			if (us122l->first == file)
				polled = &s->periods_polled;
			else
				polled = &us122l->second_periods_polled;
			if (*polled != s->periods_done) {
				*polled = s->periods_done;
				mask = EPOLLIN | EPOLLOUT | EPOLLWRNORM;
			} else
				mask = 0;
		}
		mutex_unlock(&us122l->mutex);
	}
	return mask;
}