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
typedef  int /*<<< orphan*/  PullFilter ;

/* Variables and functions */
 int PXE_PGP_CORRUPT_DATA ; 
 int pullf_read (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  px_debug (char*) ; 

int
pgp_expect_packet_end(PullFilter *pkt)
{
	int			res;
	uint8	   *tmp;

	res = pullf_read(pkt, 32 * 1024, &tmp);
	if (res > 0)
	{
		px_debug("pgp_expect_packet_end: got data");
		return PXE_PGP_CORRUPT_DATA;
	}
	return res;
}