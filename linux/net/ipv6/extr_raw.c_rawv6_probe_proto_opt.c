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
struct raw6_frag_vec {int hlen; int /*<<< orphan*/ * c; int /*<<< orphan*/  msg; } ;
struct flowi6 {int flowi6_proto; int /*<<< orphan*/  fl6_mh_type; int /*<<< orphan*/  fl6_icmp_code; int /*<<< orphan*/  fl6_icmp_type; } ;

/* Variables and functions */
#define  IPPROTO_ICMPV6 129 
#define  IPPROTO_MH 128 
 int memcpy_from_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rawv6_probe_proto_opt(struct raw6_frag_vec *rfv, struct flowi6 *fl6)
{
	int err = 0;
	switch (fl6->flowi6_proto) {
	case IPPROTO_ICMPV6:
		rfv->hlen = 2;
		err = memcpy_from_msg(rfv->c, rfv->msg, rfv->hlen);
		if (!err) {
			fl6->fl6_icmp_type = rfv->c[0];
			fl6->fl6_icmp_code = rfv->c[1];
		}
		break;
	case IPPROTO_MH:
		rfv->hlen = 4;
		err = memcpy_from_msg(rfv->c, rfv->msg, rfv->hlen);
		if (!err)
			fl6->fl6_mh_type = rfv->c[2];
	}
	return err;
}