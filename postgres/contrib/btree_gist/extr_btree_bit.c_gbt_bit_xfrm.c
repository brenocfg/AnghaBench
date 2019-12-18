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
typedef  int /*<<< orphan*/  bytea ;

/* Variables and functions */
 int INTALIGN (int) ; 
 int /*<<< orphan*/  SET_VARSIZE (int /*<<< orphan*/ *,int) ; 
 int VARBITBYTES (int /*<<< orphan*/ *) ; 
 scalar_t__ VARBITS (int /*<<< orphan*/ *) ; 
 scalar_t__ VARDATA (int /*<<< orphan*/ *) ; 
 int VARHDRSZ ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 scalar_t__ palloc (int) ; 

__attribute__((used)) static bytea *
gbt_bit_xfrm(bytea *leaf)
{
	bytea	   *out = leaf;
	int			sz = VARBITBYTES(leaf) + VARHDRSZ;
	int			padded_sz = INTALIGN(sz);

	out = (bytea *) palloc(padded_sz);
	/* initialize the padding bytes to zero */
	while (sz < padded_sz)
		((char *) out)[sz++] = 0;
	SET_VARSIZE(out, padded_sz);
	memcpy((void *) VARDATA(out), (void *) VARBITS(leaf), VARBITBYTES(leaf));
	return out;
}