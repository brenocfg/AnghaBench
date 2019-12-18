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
 int pgp_skip_packet (int /*<<< orphan*/ *) ; 
 int pullf_read_fixed (int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static int
read_pubenc_keyid(PullFilter *pkt, uint8 *keyid_buf)
{
	uint8		ver;
	int			res;

	GETBYTE(pkt, ver);
	if (ver != 3)
		return -1;

	res = pullf_read_fixed(pkt, 8, keyid_buf);
	if (res < 0)
		return res;

	return pgp_skip_packet(pkt);
}