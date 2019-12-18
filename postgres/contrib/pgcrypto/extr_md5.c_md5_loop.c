#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_4__ {unsigned int md5_n; unsigned int md5_i; int /*<<< orphan*/  const* md5_buf; } ;
typedef  TYPE_1__ md5_ctxt ;

/* Variables and functions */
 unsigned int MD5_BUFLEN ; 
 int /*<<< orphan*/  md5_calc (int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 

void
md5_loop(md5_ctxt *ctxt, const uint8 *input, unsigned len)
{
	unsigned int gap,
				i;

	ctxt->md5_n += len * 8;		/* byte to bit */
	gap = MD5_BUFLEN - ctxt->md5_i;

	if (len >= gap)
	{
		memmove(ctxt->md5_buf + ctxt->md5_i, input, gap);
		md5_calc(ctxt->md5_buf, ctxt);

		for (i = gap; i + MD5_BUFLEN <= len; i += MD5_BUFLEN)
			md5_calc(input + i, ctxt);

		ctxt->md5_i = len - i;
		memmove(ctxt->md5_buf, input + i, ctxt->md5_i);
	}
	else
	{
		memmove(ctxt->md5_buf + ctxt->md5_i, input, len);
		ctxt->md5_i += len;
	}
}