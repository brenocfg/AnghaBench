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
struct TYPE_3__ {int /*<<< orphan*/  code; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {TYPE_1__ icmph; int /*<<< orphan*/  c; } ;
struct raw_frag_vec {int hlen; TYPE_2__ hdr; int /*<<< orphan*/  msg; } ;
struct flowi4 {scalar_t__ flowi4_proto; int /*<<< orphan*/  fl4_icmp_code; int /*<<< orphan*/  fl4_icmp_type; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_ICMP ; 
 int memcpy_from_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int raw_probe_proto_opt(struct raw_frag_vec *rfv, struct flowi4 *fl4)
{
	int err;

	if (fl4->flowi4_proto != IPPROTO_ICMP)
		return 0;

	/* We only need the first two bytes. */
	rfv->hlen = 2;

	err = memcpy_from_msg(rfv->hdr.c, rfv->msg, rfv->hlen);
	if (err)
		return err;

	fl4->fl4_icmp_type = rfv->hdr.icmph.type;
	fl4->fl4_icmp_code = rfv->hdr.icmph.code;

	return 0;
}