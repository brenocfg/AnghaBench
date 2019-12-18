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
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_4__ {size_t* b64; } ;
struct TYPE_3__ {int /*<<< orphan*/ * b8; } ;
struct sha1_ctxt {TYPE_2__ c; TYPE_1__ m; } ;

/* Variables and functions */
 int COUNT ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  sha1_step (struct sha1_ctxt*) ; 

void
sha1_loop(struct sha1_ctxt *ctxt, const uint8 *input0, size_t len)
{
	const uint8 *input;
	size_t		gaplen;
	size_t		gapstart;
	size_t		off;
	size_t		copysiz;

	input = (const uint8 *) input0;
	off = 0;

	while (off < len)
	{
		gapstart = COUNT % 64;
		gaplen = 64 - gapstart;

		copysiz = (gaplen < len - off) ? gaplen : len - off;
		memmove(&ctxt->m.b8[gapstart], &input[off], copysiz);
		COUNT += copysiz;
		COUNT %= 64;
		ctxt->c.b64[0] += copysiz * 8;
		if (COUNT % 64 == 0)
			sha1_step(ctxt);
		off += copysiz;
	}
}