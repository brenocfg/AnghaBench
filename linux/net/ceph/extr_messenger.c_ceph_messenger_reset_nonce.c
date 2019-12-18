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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int /*<<< orphan*/  nonce; } ;
struct TYPE_4__ {TYPE_1__ addr; } ;
struct ceph_messenger {TYPE_2__ inst; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  encode_my_addr (struct ceph_messenger*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

void ceph_messenger_reset_nonce(struct ceph_messenger *msgr)
{
	u32 nonce = le32_to_cpu(msgr->inst.addr.nonce) + 1000000;
	msgr->inst.addr.nonce = cpu_to_le32(nonce);
	encode_my_addr(msgr);
}