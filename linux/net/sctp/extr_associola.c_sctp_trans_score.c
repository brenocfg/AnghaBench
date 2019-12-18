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
typedef  int u8 ;
struct sctp_transport {int state; } ;

/* Variables and functions */
#define  SCTP_ACTIVE 130 
#define  SCTP_PF 129 
#define  SCTP_UNKNOWN 128 

__attribute__((used)) static u8 sctp_trans_score(const struct sctp_transport *trans)
{
	switch (trans->state) {
	case SCTP_ACTIVE:
		return 3;	/* best case */
	case SCTP_UNKNOWN:
		return 2;
	case SCTP_PF:
		return 1;
	default: /* case SCTP_INACTIVE */
		return 0;	/* worst case */
	}
}