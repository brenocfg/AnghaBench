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
struct MDCBufData {scalar_t__ avail; scalar_t__ pos; scalar_t__ buf; int buflen; int mdc_avail; scalar_t__ mdc_buf; } ;
typedef  int /*<<< orphan*/  PullFilter ;

/* Variables and functions */
 int mdcbuf_finish (struct MDCBufData*) ; 
 int /*<<< orphan*/  mdcbuf_load_data (struct MDCBufData*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mdcbuf_load_mdc (struct MDCBufData*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 
 int pullf_read (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
mdcbuf_refill(struct MDCBufData *st, PullFilter *src)
{
	uint8	   *data;
	int			res;
	int			need;

	/* put avail data in start */
	if (st->avail > 0 && st->pos != st->buf)
		memmove(st->buf, st->pos, st->avail);
	st->pos = st->buf;

	/* read new data */
	need = st->buflen + 22 - st->avail - st->mdc_avail;
	res = pullf_read(src, need, &data);
	if (res < 0)
		return res;
	if (res == 0)
		return mdcbuf_finish(st);

	/* add to buffer */
	if (res >= 22)
	{
		mdcbuf_load_data(st, st->mdc_buf, st->mdc_avail);
		st->mdc_avail = 0;

		mdcbuf_load_data(st, data, res - 22);
		mdcbuf_load_mdc(st, data + res - 22, 22);
	}
	else
	{
		int			canmove = st->mdc_avail + res - 22;

		if (canmove > 0)
		{
			mdcbuf_load_data(st, st->mdc_buf, canmove);
			st->mdc_avail -= canmove;
			memmove(st->mdc_buf, st->mdc_buf + canmove, st->mdc_avail);
		}
		mdcbuf_load_mdc(st, data, res);
	}
	return 0;
}