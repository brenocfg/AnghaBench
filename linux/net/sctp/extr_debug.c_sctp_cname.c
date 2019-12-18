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
union sctp_subtype {size_t chunk; } ;

/* Variables and functions */
#define  SCTP_CID_ASCONF 134 
#define  SCTP_CID_ASCONF_ACK 133 
#define  SCTP_CID_AUTH 132 
 size_t SCTP_CID_BASE_MAX ; 
#define  SCTP_CID_FWD_TSN 131 
#define  SCTP_CID_I_DATA 130 
#define  SCTP_CID_I_FWD_TSN 129 
#define  SCTP_CID_RECONF 128 
 char const** sctp_cid_tbl ; 

const char *sctp_cname(const union sctp_subtype cid)
{
	if (cid.chunk <= SCTP_CID_BASE_MAX)
		return sctp_cid_tbl[cid.chunk];

	switch (cid.chunk) {
	case SCTP_CID_ASCONF:
		return "ASCONF";

	case SCTP_CID_ASCONF_ACK:
		return "ASCONF_ACK";

	case SCTP_CID_FWD_TSN:
		return "FWD_TSN";

	case SCTP_CID_AUTH:
		return "AUTH";

	case SCTP_CID_RECONF:
		return "RECONF";

	case SCTP_CID_I_DATA:
		return "I_DATA";

	case SCTP_CID_I_FWD_TSN:
		return "I_FWD_TSN";

	default:
		break;
	}

	return "unknown chunk";
}