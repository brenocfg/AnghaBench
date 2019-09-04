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
typedef  enum transport_state_table { ____Placeholder_transport_state_table } transport_state_table ;

/* Variables and functions */
#define  TRANSPORT_COMPLETE 136 
#define  TRANSPORT_COMPLETE_QF_ERR 135 
#define  TRANSPORT_COMPLETE_QF_OK 134 
#define  TRANSPORT_COMPLETE_QF_WP 133 
#define  TRANSPORT_ISTATE_PROCESSING 132 
#define  TRANSPORT_NEW_CMD 131 
#define  TRANSPORT_NO_STATE 130 
#define  TRANSPORT_PROCESSING 129 
#define  TRANSPORT_WRITE_PENDING 128 

__attribute__((used)) static const char *cmd_state_name(enum transport_state_table t)
{
	switch (t) {
	case TRANSPORT_NO_STATE:	return "NO_STATE";
	case TRANSPORT_NEW_CMD:		return "NEW_CMD";
	case TRANSPORT_WRITE_PENDING:	return "WRITE_PENDING";
	case TRANSPORT_PROCESSING:	return "PROCESSING";
	case TRANSPORT_COMPLETE:	return "COMPLETE";
	case TRANSPORT_ISTATE_PROCESSING:
					return "ISTATE_PROCESSING";
	case TRANSPORT_COMPLETE_QF_WP:	return "COMPLETE_QF_WP";
	case TRANSPORT_COMPLETE_QF_OK:	return "COMPLETE_QF_OK";
	case TRANSPORT_COMPLETE_QF_ERR:	return "COMPLETE_QF_ERR";
	}

	return "(?)";
}