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
struct TYPE_3__ {int state; } ;
struct TYPE_4__ {TYPE_1__ dccp; } ;
struct nf_conn {TYPE_2__ proto; } ;

/* Variables and functions */
#define  CT_DCCP_CLOSEREQ 130 
#define  CT_DCCP_CLOSING 129 
#define  CT_DCCP_TIMEWAIT 128 

__attribute__((used)) static bool dccp_can_early_drop(const struct nf_conn *ct)
{
	switch (ct->proto.dccp.state) {
	case CT_DCCP_CLOSEREQ:
	case CT_DCCP_CLOSING:
	case CT_DCCP_TIMEWAIT:
		return true;
	default:
		break;
	}

	return false;
}