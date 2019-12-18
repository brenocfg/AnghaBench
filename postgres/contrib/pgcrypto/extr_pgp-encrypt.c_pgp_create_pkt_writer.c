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
typedef  int /*<<< orphan*/  PushFilter ;

/* Variables and functions */
 int /*<<< orphan*/  pkt_stream_filter ; 
 int pushf_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int write_tag_only (int /*<<< orphan*/ *,int) ; 

int
pgp_create_pkt_writer(PushFilter *dst, int tag, PushFilter **res_p)
{
	int			res;

	res = write_tag_only(dst, tag);
	if (res < 0)
		return res;

	return pushf_create(res_p, &pkt_stream_filter, NULL, dst);
}