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
typedef  int /*<<< orphan*/  umode_t ;

/* Variables and functions */
#define  ISCSI_HOST_PARAM 165 
#define  ISCSI_HOST_PARAM_HWADDRESS 164 
#define  ISCSI_HOST_PARAM_INITIATOR_NAME 163 
#define  ISCSI_HOST_PARAM_IPADDRESS 162 
#define  ISCSI_HOST_PARAM_NETDEV_NAME 161 
#define  ISCSI_PARAM 160 
#define  ISCSI_PARAM_ABORT_TMO 159 
#define  ISCSI_PARAM_CONN_ADDRESS 158 
#define  ISCSI_PARAM_CONN_PORT 157 
#define  ISCSI_PARAM_DATADGST_EN 156 
#define  ISCSI_PARAM_DATASEQ_INORDER_EN 155 
#define  ISCSI_PARAM_ERL 154 
#define  ISCSI_PARAM_EXP_STATSN 153 
#define  ISCSI_PARAM_FAST_ABORT 152 
#define  ISCSI_PARAM_FIRST_BURST 151 
#define  ISCSI_PARAM_HDRDGST_EN 150 
#define  ISCSI_PARAM_IFACE_NAME 149 
#define  ISCSI_PARAM_IMM_DATA_EN 148 
#define  ISCSI_PARAM_INITIAL_R2T_EN 147 
#define  ISCSI_PARAM_INITIATOR_NAME 146 
#define  ISCSI_PARAM_LOCAL_PORT 145 
#define  ISCSI_PARAM_LU_RESET_TMO 144 
#define  ISCSI_PARAM_MAX_BURST 143 
#define  ISCSI_PARAM_MAX_R2T 142 
#define  ISCSI_PARAM_MAX_RECV_DLENGTH 141 
#define  ISCSI_PARAM_MAX_XMIT_DLENGTH 140 
#define  ISCSI_PARAM_PASSWORD 139 
#define  ISCSI_PARAM_PASSWORD_IN 138 
#define  ISCSI_PARAM_PDU_INORDER_EN 137 
#define  ISCSI_PARAM_PERSISTENT_ADDRESS 136 
#define  ISCSI_PARAM_PERSISTENT_PORT 135 
#define  ISCSI_PARAM_PING_TMO 134 
#define  ISCSI_PARAM_RECV_TMO 133 
#define  ISCSI_PARAM_TARGET_NAME 132 
#define  ISCSI_PARAM_TGT_RESET_TMO 131 
#define  ISCSI_PARAM_TPGT 130 
#define  ISCSI_PARAM_USERNAME 129 
#define  ISCSI_PARAM_USERNAME_IN 128 
 int /*<<< orphan*/  S_IRUGO ; 

__attribute__((used)) static umode_t iscsi_sw_tcp_attr_is_visible(int param_type, int param)
{
	switch (param_type) {
	case ISCSI_HOST_PARAM:
		switch (param) {
		case ISCSI_HOST_PARAM_NETDEV_NAME:
		case ISCSI_HOST_PARAM_HWADDRESS:
		case ISCSI_HOST_PARAM_IPADDRESS:
		case ISCSI_HOST_PARAM_INITIATOR_NAME:
			return S_IRUGO;
		default:
			return 0;
		}
	case ISCSI_PARAM:
		switch (param) {
		case ISCSI_PARAM_MAX_RECV_DLENGTH:
		case ISCSI_PARAM_MAX_XMIT_DLENGTH:
		case ISCSI_PARAM_HDRDGST_EN:
		case ISCSI_PARAM_DATADGST_EN:
		case ISCSI_PARAM_CONN_ADDRESS:
		case ISCSI_PARAM_CONN_PORT:
		case ISCSI_PARAM_LOCAL_PORT:
		case ISCSI_PARAM_EXP_STATSN:
		case ISCSI_PARAM_PERSISTENT_ADDRESS:
		case ISCSI_PARAM_PERSISTENT_PORT:
		case ISCSI_PARAM_PING_TMO:
		case ISCSI_PARAM_RECV_TMO:
		case ISCSI_PARAM_INITIAL_R2T_EN:
		case ISCSI_PARAM_MAX_R2T:
		case ISCSI_PARAM_IMM_DATA_EN:
		case ISCSI_PARAM_FIRST_BURST:
		case ISCSI_PARAM_MAX_BURST:
		case ISCSI_PARAM_PDU_INORDER_EN:
		case ISCSI_PARAM_DATASEQ_INORDER_EN:
		case ISCSI_PARAM_ERL:
		case ISCSI_PARAM_TARGET_NAME:
		case ISCSI_PARAM_TPGT:
		case ISCSI_PARAM_USERNAME:
		case ISCSI_PARAM_PASSWORD:
		case ISCSI_PARAM_USERNAME_IN:
		case ISCSI_PARAM_PASSWORD_IN:
		case ISCSI_PARAM_FAST_ABORT:
		case ISCSI_PARAM_ABORT_TMO:
		case ISCSI_PARAM_LU_RESET_TMO:
		case ISCSI_PARAM_TGT_RESET_TMO:
		case ISCSI_PARAM_IFACE_NAME:
		case ISCSI_PARAM_INITIATOR_NAME:
			return S_IRUGO;
		default:
			return 0;
		}
	}

	return 0;
}