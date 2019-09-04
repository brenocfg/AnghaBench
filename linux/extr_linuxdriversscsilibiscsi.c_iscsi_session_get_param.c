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
struct iscsi_session {int fast_abort; int abort_timeout; int lu_reset_timeout; int tgt_reset_timeout; int initial_r2t_en; int imm_data_en; int first_burst; int max_burst; int pdu_inorder_en; int dataseq_inorder_en; int def_taskmgmt_tmo; int erl; char* targetname; char* targetalias; int tpgt; char* username; char* username_in; char* password; char* password_in; char* ifacename; char* initiatorname; char* boot_root; char* boot_nic; char* boot_target; int auto_snd_tgt_disable; int discovery_sess; char* portal_type; int chap_auth_en; int discovery_logout_en; int bidi_chap_en; int discovery_auth_optional; int time2wait; int time2retain; int tsid; int* isid; int discovery_parent_idx; char* discovery_parent_type; int /*<<< orphan*/  max_r2t; } ;
struct iscsi_cls_session {struct iscsi_session* dd_data; } ;
typedef  enum iscsi_param { ____Placeholder_iscsi_param } iscsi_param ;

/* Variables and functions */
 int ENOSYS ; 
#define  ISCSI_PARAM_ABORT_TMO 165 
#define  ISCSI_PARAM_AUTO_SND_TGT_DISABLE 164 
#define  ISCSI_PARAM_BIDI_CHAP_EN 163 
#define  ISCSI_PARAM_BOOT_NIC 162 
#define  ISCSI_PARAM_BOOT_ROOT 161 
#define  ISCSI_PARAM_BOOT_TARGET 160 
#define  ISCSI_PARAM_CHAP_AUTH_EN 159 
#define  ISCSI_PARAM_DATASEQ_INORDER_EN 158 
#define  ISCSI_PARAM_DEF_TASKMGMT_TMO 157 
#define  ISCSI_PARAM_DEF_TIME2RETAIN 156 
#define  ISCSI_PARAM_DEF_TIME2WAIT 155 
#define  ISCSI_PARAM_DISCOVERY_AUTH_OPTIONAL 154 
#define  ISCSI_PARAM_DISCOVERY_LOGOUT_EN 153 
#define  ISCSI_PARAM_DISCOVERY_PARENT_IDX 152 
#define  ISCSI_PARAM_DISCOVERY_PARENT_TYPE 151 
#define  ISCSI_PARAM_DISCOVERY_SESS 150 
#define  ISCSI_PARAM_ERL 149 
#define  ISCSI_PARAM_FAST_ABORT 148 
#define  ISCSI_PARAM_FIRST_BURST 147 
#define  ISCSI_PARAM_IFACE_NAME 146 
#define  ISCSI_PARAM_IMM_DATA_EN 145 
#define  ISCSI_PARAM_INITIAL_R2T_EN 144 
#define  ISCSI_PARAM_INITIATOR_NAME 143 
#define  ISCSI_PARAM_ISID 142 
#define  ISCSI_PARAM_LU_RESET_TMO 141 
#define  ISCSI_PARAM_MAX_BURST 140 
#define  ISCSI_PARAM_MAX_R2T 139 
#define  ISCSI_PARAM_PASSWORD 138 
#define  ISCSI_PARAM_PASSWORD_IN 137 
#define  ISCSI_PARAM_PDU_INORDER_EN 136 
#define  ISCSI_PARAM_PORTAL_TYPE 135 
#define  ISCSI_PARAM_TARGET_ALIAS 134 
#define  ISCSI_PARAM_TARGET_NAME 133 
#define  ISCSI_PARAM_TGT_RESET_TMO 132 
#define  ISCSI_PARAM_TPGT 131 
#define  ISCSI_PARAM_TSID 130 
#define  ISCSI_PARAM_USERNAME 129 
#define  ISCSI_PARAM_USERNAME_IN 128 
 int sprintf (char*,char*,...) ; 

int iscsi_session_get_param(struct iscsi_cls_session *cls_session,
			    enum iscsi_param param, char *buf)
{
	struct iscsi_session *session = cls_session->dd_data;
	int len;

	switch(param) {
	case ISCSI_PARAM_FAST_ABORT:
		len = sprintf(buf, "%d\n", session->fast_abort);
		break;
	case ISCSI_PARAM_ABORT_TMO:
		len = sprintf(buf, "%d\n", session->abort_timeout);
		break;
	case ISCSI_PARAM_LU_RESET_TMO:
		len = sprintf(buf, "%d\n", session->lu_reset_timeout);
		break;
	case ISCSI_PARAM_TGT_RESET_TMO:
		len = sprintf(buf, "%d\n", session->tgt_reset_timeout);
		break;
	case ISCSI_PARAM_INITIAL_R2T_EN:
		len = sprintf(buf, "%d\n", session->initial_r2t_en);
		break;
	case ISCSI_PARAM_MAX_R2T:
		len = sprintf(buf, "%hu\n", session->max_r2t);
		break;
	case ISCSI_PARAM_IMM_DATA_EN:
		len = sprintf(buf, "%d\n", session->imm_data_en);
		break;
	case ISCSI_PARAM_FIRST_BURST:
		len = sprintf(buf, "%u\n", session->first_burst);
		break;
	case ISCSI_PARAM_MAX_BURST:
		len = sprintf(buf, "%u\n", session->max_burst);
		break;
	case ISCSI_PARAM_PDU_INORDER_EN:
		len = sprintf(buf, "%d\n", session->pdu_inorder_en);
		break;
	case ISCSI_PARAM_DATASEQ_INORDER_EN:
		len = sprintf(buf, "%d\n", session->dataseq_inorder_en);
		break;
	case ISCSI_PARAM_DEF_TASKMGMT_TMO:
		len = sprintf(buf, "%d\n", session->def_taskmgmt_tmo);
		break;
	case ISCSI_PARAM_ERL:
		len = sprintf(buf, "%d\n", session->erl);
		break;
	case ISCSI_PARAM_TARGET_NAME:
		len = sprintf(buf, "%s\n", session->targetname);
		break;
	case ISCSI_PARAM_TARGET_ALIAS:
		len = sprintf(buf, "%s\n", session->targetalias);
		break;
	case ISCSI_PARAM_TPGT:
		len = sprintf(buf, "%d\n", session->tpgt);
		break;
	case ISCSI_PARAM_USERNAME:
		len = sprintf(buf, "%s\n", session->username);
		break;
	case ISCSI_PARAM_USERNAME_IN:
		len = sprintf(buf, "%s\n", session->username_in);
		break;
	case ISCSI_PARAM_PASSWORD:
		len = sprintf(buf, "%s\n", session->password);
		break;
	case ISCSI_PARAM_PASSWORD_IN:
		len = sprintf(buf, "%s\n", session->password_in);
		break;
	case ISCSI_PARAM_IFACE_NAME:
		len = sprintf(buf, "%s\n", session->ifacename);
		break;
	case ISCSI_PARAM_INITIATOR_NAME:
		len = sprintf(buf, "%s\n", session->initiatorname);
		break;
	case ISCSI_PARAM_BOOT_ROOT:
		len = sprintf(buf, "%s\n", session->boot_root);
		break;
	case ISCSI_PARAM_BOOT_NIC:
		len = sprintf(buf, "%s\n", session->boot_nic);
		break;
	case ISCSI_PARAM_BOOT_TARGET:
		len = sprintf(buf, "%s\n", session->boot_target);
		break;
	case ISCSI_PARAM_AUTO_SND_TGT_DISABLE:
		len = sprintf(buf, "%u\n", session->auto_snd_tgt_disable);
		break;
	case ISCSI_PARAM_DISCOVERY_SESS:
		len = sprintf(buf, "%u\n", session->discovery_sess);
		break;
	case ISCSI_PARAM_PORTAL_TYPE:
		len = sprintf(buf, "%s\n", session->portal_type);
		break;
	case ISCSI_PARAM_CHAP_AUTH_EN:
		len = sprintf(buf, "%u\n", session->chap_auth_en);
		break;
	case ISCSI_PARAM_DISCOVERY_LOGOUT_EN:
		len = sprintf(buf, "%u\n", session->discovery_logout_en);
		break;
	case ISCSI_PARAM_BIDI_CHAP_EN:
		len = sprintf(buf, "%u\n", session->bidi_chap_en);
		break;
	case ISCSI_PARAM_DISCOVERY_AUTH_OPTIONAL:
		len = sprintf(buf, "%u\n", session->discovery_auth_optional);
		break;
	case ISCSI_PARAM_DEF_TIME2WAIT:
		len = sprintf(buf, "%d\n", session->time2wait);
		break;
	case ISCSI_PARAM_DEF_TIME2RETAIN:
		len = sprintf(buf, "%d\n", session->time2retain);
		break;
	case ISCSI_PARAM_TSID:
		len = sprintf(buf, "%u\n", session->tsid);
		break;
	case ISCSI_PARAM_ISID:
		len = sprintf(buf, "%02x%02x%02x%02x%02x%02x\n",
			      session->isid[0], session->isid[1],
			      session->isid[2], session->isid[3],
			      session->isid[4], session->isid[5]);
		break;
	case ISCSI_PARAM_DISCOVERY_PARENT_IDX:
		len = sprintf(buf, "%u\n", session->discovery_parent_idx);
		break;
	case ISCSI_PARAM_DISCOVERY_PARENT_TYPE:
		if (session->discovery_parent_type)
			len = sprintf(buf, "%s\n",
				      session->discovery_parent_type);
		else
			len = sprintf(buf, "\n");
		break;
	default:
		return -ENOSYS;
	}

	return len;
}