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
typedef  int /*<<< orphan*/  uint8 ;
struct MDCBufData {int avail; int /*<<< orphan*/ * pos; int /*<<< orphan*/  eof; } ;
typedef  int /*<<< orphan*/  PullFilter ;

/* Variables and functions */
 int mdcbuf_refill (struct MDCBufData*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mdcbuf_read(void *priv, PullFilter *src, int len,
			uint8 **data_p, uint8 *buf, int buflen)
{
	struct MDCBufData *st = priv;
	int			res;

	if (!st->eof && len > st->avail)
	{
		res = mdcbuf_refill(st, src);
		if (res < 0)
			return res;
	}

	if (len > st->avail)
		len = st->avail;

	*data_p = st->pos;
	st->pos += len;
	st->avail -= len;
	return len;
}