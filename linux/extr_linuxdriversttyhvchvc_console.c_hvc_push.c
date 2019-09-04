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
struct hvc_struct {int n_outbuf; int do_wakeup; int /*<<< orphan*/  outbuf; int /*<<< orphan*/  vtermno; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* put_chars ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hvc_push(struct hvc_struct *hp)
{
	int n;

	n = hp->ops->put_chars(hp->vtermno, hp->outbuf, hp->n_outbuf);
	if (n <= 0) {
		if (n == 0 || n == -EAGAIN) {
			hp->do_wakeup = 1;
			return 0;
		}
		/* throw away output on error; this happens when
		   there is no session connected to the vterm. */
		hp->n_outbuf = 0;
	} else
		hp->n_outbuf -= n;
	if (hp->n_outbuf > 0)
		memmove(hp->outbuf, hp->outbuf + n, hp->n_outbuf);
	else
		hp->do_wakeup = 1;

	return n;
}