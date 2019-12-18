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
 int pullf_read (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 

int
pgp_skip_packet(PullFilter *pkt)
{
	int			res = 1;
	uint8	   *tmp;

	while (res > 0)
		res = pullf_read(pkt, 32 * 1024, &tmp);
	return res;
}