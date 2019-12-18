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
typedef  int uint8 ;
typedef  int /*<<< orphan*/  PullFilter ;

/* Variables and functions */
 int PKT_CONTEXT ; 
 int PXE_PGP_CORRUPT_DATA ; 
 int parse_new_len (int /*<<< orphan*/ *,int*) ; 
 int parse_old_len (int /*<<< orphan*/ *,int*,int) ; 
 int pullf_read (int /*<<< orphan*/ *,int,int**) ; 
 int /*<<< orphan*/  px_debug (char*) ; 

int
pgp_parse_pkt_hdr(PullFilter *src, uint8 *tag, int *len_p, int allow_ctx)
{
	int			lentype;
	int			res;
	uint8	   *p;

	/* EOF is normal here, thus we don't use GETBYTE */
	res = pullf_read(src, 1, &p);
	if (res < 0)
		return res;
	if (res == 0)
		return 0;

	if ((*p & 0x80) == 0)
	{
		px_debug("pgp_parse_pkt_hdr: not pkt hdr");
		return PXE_PGP_CORRUPT_DATA;
	}

	if (*p & 0x40)
	{
		*tag = *p & 0x3f;
		res = parse_new_len(src, len_p);
	}
	else
	{
		lentype = *p & 3;
		*tag = (*p >> 2) & 0x0F;
		if (lentype == 3)
			res = allow_ctx ? PKT_CONTEXT : PXE_PGP_CORRUPT_DATA;
		else
			res = parse_old_len(src, len_p, lentype);
	}
	return res;
}