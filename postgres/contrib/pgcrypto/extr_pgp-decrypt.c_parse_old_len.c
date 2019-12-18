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
 int /*<<< orphan*/  GETBYTE (int /*<<< orphan*/ *,int) ; 
 int MAX_CHUNK ; 
 int PKT_NORMAL ; 
 int PXE_PGP_CORRUPT_DATA ; 
 int /*<<< orphan*/  px_debug (char*) ; 

__attribute__((used)) static int
parse_old_len(PullFilter *src, int *len_p, int lentype)
{
	uint8		b;
	int			len;

	GETBYTE(src, b);
	len = b;

	if (lentype == 1)
	{
		GETBYTE(src, b);
		len = (len << 8) | b;
	}
	else if (lentype == 2)
	{
		GETBYTE(src, b);
		len = (len << 8) | b;
		GETBYTE(src, b);
		len = (len << 8) | b;
		GETBYTE(src, b);
		len = (len << 8) | b;
	}

	if (len < 0 || len > MAX_CHUNK)
	{
		px_debug("parse_old_len: weird length");
		return PXE_PGP_CORRUPT_DATA;
	}
	*len_p = len;
	return PKT_NORMAL;
}