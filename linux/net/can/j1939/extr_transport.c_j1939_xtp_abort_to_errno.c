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
struct j1939_priv {int /*<<< orphan*/  ndev; } ;
typedef  enum j1939_xtp_abort { ____Placeholder_j1939_xtp_abort } j1939_xtp_abort ;

/* Variables and functions */
 int EALREADY ; 
 int EBADMSG ; 
 int EHOSTUNREACH ; 
 int EILSEQ ; 
 int EMSGSIZE ; 
 int ENOTCONN ; 
 int ENOTRECOVERABLE ; 
 int EPROTO ; 
#define  J1939_XTP_ABORT_BAD_EDPO_OFFSET 144 
#define  J1939_XTP_ABORT_BAD_EDPO_PGN 143 
#define  J1939_XTP_ABORT_BAD_SEQ 142 
#define  J1939_XTP_ABORT_BUSY 141 
#define  J1939_XTP_ABORT_DUP_SEQ 140 
#define  J1939_XTP_ABORT_ECTS_TOO_BIG 139 
#define  J1939_XTP_ABORT_ECTS_UNXPECTED_PGN 138 
#define  J1939_XTP_ABORT_EDPO_OUTOF_CTS 137 
#define  J1939_XTP_ABORT_EDPO_UNEXPECTED 136 
#define  J1939_XTP_ABORT_FAULT 135 
#define  J1939_XTP_ABORT_GENERIC 134 
#define  J1939_XTP_ABORT_OTHER 133 
#define  J1939_XTP_ABORT_OTHER_DEPRECATED 132 
#define  J1939_XTP_ABORT_RESOURCE 131 
#define  J1939_XTP_ABORT_TIMEOUT 130 
#define  J1939_XTP_ABORT_UNEXPECTED_DATA 129 
#define  J1939_XTP_NO_ABORT 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int j1939_xtp_abort_to_errno(struct j1939_priv *priv,
				    enum j1939_xtp_abort abort)
{
	int err;

	switch (abort) {
	case J1939_XTP_NO_ABORT:
		WARN_ON_ONCE(abort == J1939_XTP_NO_ABORT);
		err = 0;
		break;
	case J1939_XTP_ABORT_BUSY:
		err = EALREADY;
		break;
	case J1939_XTP_ABORT_RESOURCE:
		err = EMSGSIZE;
		break;
	case J1939_XTP_ABORT_TIMEOUT:
		err = EHOSTUNREACH;
		break;
	case J1939_XTP_ABORT_GENERIC:
		err = EBADMSG;
		break;
	case J1939_XTP_ABORT_FAULT:
		err = ENOTRECOVERABLE;
		break;
	case J1939_XTP_ABORT_UNEXPECTED_DATA:
		err = ENOTCONN;
		break;
	case J1939_XTP_ABORT_BAD_SEQ:
		err = EILSEQ;
		break;
	case J1939_XTP_ABORT_DUP_SEQ:
		err = EPROTO;
		break;
	case J1939_XTP_ABORT_EDPO_UNEXPECTED:
		err = EPROTO;
		break;
	case J1939_XTP_ABORT_BAD_EDPO_PGN:
		err = EPROTO;
		break;
	case J1939_XTP_ABORT_EDPO_OUTOF_CTS:
		err = EPROTO;
		break;
	case J1939_XTP_ABORT_BAD_EDPO_OFFSET:
		err = EPROTO;
		break;
	case J1939_XTP_ABORT_OTHER_DEPRECATED:
		err = EPROTO;
		break;
	case J1939_XTP_ABORT_ECTS_UNXPECTED_PGN:
		err = EPROTO;
		break;
	case J1939_XTP_ABORT_ECTS_TOO_BIG:
		err = EPROTO;
		break;
	case J1939_XTP_ABORT_OTHER:
		err = EPROTO;
		break;
	default:
		netdev_warn(priv->ndev, "Unknown abort code %i", abort);
		err = EPROTO;
	}

	return err;
}