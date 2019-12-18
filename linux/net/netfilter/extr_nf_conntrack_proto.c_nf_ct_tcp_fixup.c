#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_4__ {scalar_t__ state; TYPE_2__* seen; } ;
struct TYPE_6__ {TYPE_1__ tcp; } ;
struct nf_conn {TYPE_3__ proto; } ;
struct TYPE_5__ {scalar_t__ td_maxwin; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ TCP_CONNTRACK_ESTABLISHED ; 
 scalar_t__ nf_ct_l3num (struct nf_conn*) ; 
 scalar_t__ nf_ct_protonum (struct nf_conn*) ; 

__attribute__((used)) static int nf_ct_tcp_fixup(struct nf_conn *ct, void *_nfproto)
{
	u8 nfproto = (unsigned long)_nfproto;

	if (nf_ct_l3num(ct) != nfproto)
		return 0;

	if (nf_ct_protonum(ct) == IPPROTO_TCP &&
	    ct->proto.tcp.state == TCP_CONNTRACK_ESTABLISHED) {
		ct->proto.tcp.seen[0].td_maxwin = 0;
		ct->proto.tcp.seen[1].td_maxwin = 0;
	}

	return 0;
}