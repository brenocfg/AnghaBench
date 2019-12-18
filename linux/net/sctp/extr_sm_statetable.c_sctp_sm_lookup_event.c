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
union sctp_subtype {int /*<<< orphan*/  chunk; } ;
struct sctp_sm_table_entry {int dummy; } ;
struct net {int dummy; } ;
typedef  enum sctp_state { ____Placeholder_sctp_state } sctp_state ;
typedef  enum sctp_event_type { ____Placeholder_sctp_event_type } sctp_event_type ;

/* Variables and functions */
 struct sctp_sm_table_entry const* DO_LOOKUP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_EVENT_OTHER_MAX ; 
 int /*<<< orphan*/  SCTP_EVENT_PRIMITIVE_MAX ; 
 int /*<<< orphan*/  SCTP_EVENT_TIMEOUT_MAX ; 
#define  SCTP_EVENT_T_CHUNK 131 
#define  SCTP_EVENT_T_OTHER 130 
#define  SCTP_EVENT_T_PRIMITIVE 129 
#define  SCTP_EVENT_T_TIMEOUT 128 
 struct sctp_sm_table_entry const bug ; 
 int /*<<< orphan*/  other ; 
 int /*<<< orphan*/  other_event_table ; 
 int /*<<< orphan*/  primitive ; 
 int /*<<< orphan*/  primitive_event_table ; 
 struct sctp_sm_table_entry const* sctp_chunk_event_lookup (struct net*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  timeout ; 
 int /*<<< orphan*/  timeout_event_table ; 

const struct sctp_sm_table_entry *sctp_sm_lookup_event(
					struct net *net,
					enum sctp_event_type event_type,
					enum sctp_state state,
					union sctp_subtype event_subtype)
{
	switch (event_type) {
	case SCTP_EVENT_T_CHUNK:
		return sctp_chunk_event_lookup(net, event_subtype.chunk, state);
	case SCTP_EVENT_T_TIMEOUT:
		return DO_LOOKUP(SCTP_EVENT_TIMEOUT_MAX, timeout,
				 timeout_event_table);
	case SCTP_EVENT_T_OTHER:
		return DO_LOOKUP(SCTP_EVENT_OTHER_MAX, other,
				 other_event_table);
	case SCTP_EVENT_T_PRIMITIVE:
		return DO_LOOKUP(SCTP_EVENT_PRIMITIVE_MAX, primitive,
				 primitive_event_table);
	default:
		/* Yikes!  We got an illegal event type.  */
		return &bug;
	}
}