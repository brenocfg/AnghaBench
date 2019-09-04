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
typedef  int __u8 ;

/* Variables and functions */
 int EALREADY ; 
 int EBADMSG ; 
 int EBADRQC ; 
 int EBUSY ; 
 int ECOMM ; 
 int ECONNREFUSED ; 
 int EHOSTDOWN ; 
 int EMSGSIZE ; 
 int ENOSYS ; 
 int EPROTO ; 
 int ETIMEDOUT ; 
#define  NCI_STATUS_DISCOVERY_ALREADY_STARTED 147 
#define  NCI_STATUS_DISCOVERY_TARGET_ACTIVATION_FAILED 146 
#define  NCI_STATUS_FAILED 145 
#define  NCI_STATUS_INVALID_PARAM 144 
#define  NCI_STATUS_MESSAGE_SIZE_EXCEEDED 143 
#define  NCI_STATUS_NFCEE_INTERFACE_ACTIVATION_FAILED 142 
#define  NCI_STATUS_NFCEE_PROTOCOL_ERROR 141 
#define  NCI_STATUS_NFCEE_TIMEOUT_ERROR 140 
#define  NCI_STATUS_NFCEE_TRANSMISSION_ERROR 139 
#define  NCI_STATUS_NOT_INITIALIZED 138 
#define  NCI_STATUS_OK 137 
#define  NCI_STATUS_REJECTED 136 
#define  NCI_STATUS_RF_FRAME_CORRUPTED 135 
#define  NCI_STATUS_RF_PROTOCOL_ERROR 134 
#define  NCI_STATUS_RF_TIMEOUT_ERROR 133 
#define  NCI_STATUS_RF_TRANSMISSION_ERROR 132 
#define  NCI_STATUS_SEMANTIC_ERROR 131 
#define  NCI_STATUS_SYNTAX_ERROR 130 
#define  NCI_STATUS_UNKNOWN_GID 129 
#define  NCI_STATUS_UNKNOWN_OID 128 

int nci_to_errno(__u8 code)
{
	switch (code) {
	case NCI_STATUS_OK:
		return 0;

	case NCI_STATUS_REJECTED:
		return -EBUSY;

	case NCI_STATUS_RF_FRAME_CORRUPTED:
		return -EBADMSG;

	case NCI_STATUS_NOT_INITIALIZED:
		return -EHOSTDOWN;

	case NCI_STATUS_SYNTAX_ERROR:
	case NCI_STATUS_SEMANTIC_ERROR:
	case NCI_STATUS_INVALID_PARAM:
	case NCI_STATUS_RF_PROTOCOL_ERROR:
	case NCI_STATUS_NFCEE_PROTOCOL_ERROR:
		return -EPROTO;

	case NCI_STATUS_UNKNOWN_GID:
	case NCI_STATUS_UNKNOWN_OID:
		return -EBADRQC;

	case NCI_STATUS_MESSAGE_SIZE_EXCEEDED:
		return -EMSGSIZE;

	case NCI_STATUS_DISCOVERY_ALREADY_STARTED:
		return -EALREADY;

	case NCI_STATUS_DISCOVERY_TARGET_ACTIVATION_FAILED:
	case NCI_STATUS_NFCEE_INTERFACE_ACTIVATION_FAILED:
		return -ECONNREFUSED;

	case NCI_STATUS_RF_TRANSMISSION_ERROR:
	case NCI_STATUS_NFCEE_TRANSMISSION_ERROR:
		return -ECOMM;

	case NCI_STATUS_RF_TIMEOUT_ERROR:
	case NCI_STATUS_NFCEE_TIMEOUT_ERROR:
		return -ETIMEDOUT;

	case NCI_STATUS_FAILED:
	default:
		return -ENOSYS;
	}
}