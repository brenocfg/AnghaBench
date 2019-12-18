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
struct inet6_dev {int* rndid; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_random_bytes (int*,int) ; 

__attribute__((used)) static void ipv6_regen_rndid(struct inet6_dev *idev)
{
regen:
	get_random_bytes(idev->rndid, sizeof(idev->rndid));
	idev->rndid[0] &= ~0x02;

	/*
	 * <draft-ietf-ipngwg-temp-addresses-v2-00.txt>:
	 * check if generated address is not inappropriate
	 *
	 *  - Reserved subnet anycast (RFC 2526)
	 *	11111101 11....11 1xxxxxxx
	 *  - ISATAP (RFC4214) 6.1
	 *	00-00-5E-FE-xx-xx-xx-xx
	 *  - value 0
	 *  - XXX: already assigned to an address on the device
	 */
	if (idev->rndid[0] == 0xfd &&
	    (idev->rndid[1]&idev->rndid[2]&idev->rndid[3]&idev->rndid[4]&idev->rndid[5]&idev->rndid[6]) == 0xff &&
	    (idev->rndid[7]&0x80))
		goto regen;
	if ((idev->rndid[0]|idev->rndid[1]) == 0) {
		if (idev->rndid[2] == 0x5e && idev->rndid[3] == 0xfe)
			goto regen;
		if ((idev->rndid[2]|idev->rndid[3]|idev->rndid[4]|idev->rndid[5]|idev->rndid[6]|idev->rndid[7]) == 0x00)
			goto regen;
	}
}