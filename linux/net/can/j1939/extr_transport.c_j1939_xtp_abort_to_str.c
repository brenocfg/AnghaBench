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
typedef  enum j1939_xtp_abort { ____Placeholder_j1939_xtp_abort } j1939_xtp_abort ;

/* Variables and functions */
#define  J1939_XTP_ABORT_BAD_EDPO_OFFSET 143 
#define  J1939_XTP_ABORT_BAD_EDPO_PGN 142 
#define  J1939_XTP_ABORT_BAD_SEQ 141 
#define  J1939_XTP_ABORT_BUSY 140 
#define  J1939_XTP_ABORT_DUP_SEQ 139 
#define  J1939_XTP_ABORT_ECTS_TOO_BIG 138 
#define  J1939_XTP_ABORT_ECTS_UNXPECTED_PGN 137 
#define  J1939_XTP_ABORT_EDPO_OUTOF_CTS 136 
#define  J1939_XTP_ABORT_EDPO_UNEXPECTED 135 
#define  J1939_XTP_ABORT_FAULT 134 
#define  J1939_XTP_ABORT_GENERIC 133 
#define  J1939_XTP_ABORT_OTHER 132 
#define  J1939_XTP_ABORT_OTHER_DEPRECATED 131 
#define  J1939_XTP_ABORT_RESOURCE 130 
#define  J1939_XTP_ABORT_TIMEOUT 129 
#define  J1939_XTP_ABORT_UNEXPECTED_DATA 128 

__attribute__((used)) static const char *j1939_xtp_abort_to_str(enum j1939_xtp_abort abort)
{
	switch (abort) {
	case J1939_XTP_ABORT_BUSY:
		return "Already in one or more connection managed sessions and cannot support another.";
	case J1939_XTP_ABORT_RESOURCE:
		return "System resources were needed for another task so this connection managed session was terminated.";
	case J1939_XTP_ABORT_TIMEOUT:
		return "A timeout occurred and this is the connection abort to close the session.";
	case J1939_XTP_ABORT_GENERIC:
		return "CTS messages received when data transfer is in progress";
	case J1939_XTP_ABORT_FAULT:
		return "Maximal retransmit request limit reached";
	case J1939_XTP_ABORT_UNEXPECTED_DATA:
		return "Unexpected data transfer packet";
	case J1939_XTP_ABORT_BAD_SEQ:
		return "Bad sequence number (and software is not able to recover)";
	case J1939_XTP_ABORT_DUP_SEQ:
		return "Duplicate sequence number (and software is not able to recover)";
	case J1939_XTP_ABORT_EDPO_UNEXPECTED:
		return "Unexpected EDPO packet (ETP) or Message size > 1785 bytes (TP)";
	case J1939_XTP_ABORT_BAD_EDPO_PGN:
		return "Unexpected EDPO PGN (PGN in EDPO is bad)";
	case J1939_XTP_ABORT_EDPO_OUTOF_CTS:
		return "EDPO number of packets is greater than CTS";
	case J1939_XTP_ABORT_BAD_EDPO_OFFSET:
		return "Bad EDPO offset";
	case J1939_XTP_ABORT_OTHER_DEPRECATED:
		return "Deprecated. Use 250 instead (Any other reason)";
	case J1939_XTP_ABORT_ECTS_UNXPECTED_PGN:
		return "Unexpected ECTS PGN (PGN in ECTS is bad)";
	case J1939_XTP_ABORT_ECTS_TOO_BIG:
		return "ECTS requested packets exceeds message size";
	case J1939_XTP_ABORT_OTHER:
		return "Any other reason (if a Connection Abort reason is identified that is not listed in the table use code 250)";
	default:
		return "<unknown>";
	}
}