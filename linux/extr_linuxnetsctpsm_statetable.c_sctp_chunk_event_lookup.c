#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sctp_sm_table_entry {int dummy; } ;
struct TYPE_2__ {scalar_t__ auth_enable; scalar_t__ reconf_enable; scalar_t__ addip_enable; scalar_t__ prsctp_enable; } ;
struct net {TYPE_1__ sctp; } ;
typedef  enum sctp_state { ____Placeholder_sctp_state } sctp_state ;
typedef  enum sctp_cid { ____Placeholder_sctp_cid } sctp_cid ;

/* Variables and functions */
 int SCTP_CID_ASCONF ; 
 int SCTP_CID_ASCONF_ACK ; 
 int SCTP_CID_AUTH ; 
 int SCTP_CID_BASE_MAX ; 
 int SCTP_CID_DATA ; 
 int SCTP_CID_FWD_TSN ; 
 int SCTP_CID_I_DATA ; 
 int SCTP_CID_I_FWD_TSN ; 
 int SCTP_CID_RECONF ; 
 int SCTP_STATE_MAX ; 
 struct sctp_sm_table_entry const** addip_chunk_event_table ; 
 struct sctp_sm_table_entry const** auth_chunk_event_table ; 
 struct sctp_sm_table_entry const bug ; 
 struct sctp_sm_table_entry const** chunk_event_table ; 
 struct sctp_sm_table_entry const* chunk_event_table_unknown ; 
 struct sctp_sm_table_entry const** prsctp_chunk_event_table ; 
 struct sctp_sm_table_entry const** reconf_chunk_event_table ; 

__attribute__((used)) static const struct sctp_sm_table_entry *sctp_chunk_event_lookup(
						struct net *net,
						enum sctp_cid cid,
						enum sctp_state state)
{
	if (state > SCTP_STATE_MAX)
		return &bug;

	if (cid == SCTP_CID_I_DATA)
		cid = SCTP_CID_DATA;

	if (cid <= SCTP_CID_BASE_MAX)
		return &chunk_event_table[cid][state];

	if (net->sctp.prsctp_enable) {
		if (cid == SCTP_CID_FWD_TSN || cid == SCTP_CID_I_FWD_TSN)
			return &prsctp_chunk_event_table[0][state];
	}

	if (net->sctp.addip_enable) {
		if (cid == SCTP_CID_ASCONF)
			return &addip_chunk_event_table[0][state];

		if (cid == SCTP_CID_ASCONF_ACK)
			return &addip_chunk_event_table[1][state];
	}

	if (net->sctp.reconf_enable)
		if (cid == SCTP_CID_RECONF)
			return &reconf_chunk_event_table[0][state];

	if (net->sctp.auth_enable) {
		if (cid == SCTP_CID_AUTH)
			return &auth_chunk_event_table[0][state];
	}

	return &chunk_event_table_unknown[state];
}