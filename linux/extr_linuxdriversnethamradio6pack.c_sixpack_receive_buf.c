#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int dummy; } ;
struct sixpack {TYPE_2__* dev; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_errors; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIXPF_ERROR ; 
 int /*<<< orphan*/  sixpack_decode (struct sixpack*,unsigned char const*,int) ; 
 struct sixpack* sp_get (struct tty_struct*) ; 
 int /*<<< orphan*/  sp_put (struct sixpack*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_unthrottle (struct tty_struct*) ; 

__attribute__((used)) static void sixpack_receive_buf(struct tty_struct *tty,
	const unsigned char *cp, char *fp, int count)
{
	struct sixpack *sp;
	int count1;

	if (!count)
		return;

	sp = sp_get(tty);
	if (!sp)
		return;

	/* Read the characters out of the buffer */
	count1 = count;
	while (count) {
		count--;
		if (fp && *fp++) {
			if (!test_and_set_bit(SIXPF_ERROR, &sp->flags))
				sp->dev->stats.rx_errors++;
			continue;
		}
	}
	sixpack_decode(sp, cp, count1);

	sp_put(sp);
	tty_unthrottle(tty);
}