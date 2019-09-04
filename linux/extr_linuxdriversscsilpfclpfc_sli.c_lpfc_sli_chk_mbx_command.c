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
typedef  int uint8_t ;

/* Variables and functions */
#define  MBX_ACCESS_VDATA 192 
#define  MBX_ASYNCEVT_ENABLE 191 
#define  MBX_AUTH_PORT 190 
#define  MBX_BEACON 189 
#define  MBX_CLEAR_LA 188 
#define  MBX_CONFIG_FARP 187 
#define  MBX_CONFIG_LINK 186 
#define  MBX_CONFIG_PORT 185 
#define  MBX_CONFIG_RING 184 
#define  MBX_DEL_LD_ENTRY 183 
#define  MBX_DOWN_LINK 182 
#define  MBX_DOWN_LOAD 181 
#define  MBX_DUMP_CONTEXT 180 
#define  MBX_DUMP_MEMORY 179 
#define  MBX_HEARTBEAT 178 
#define  MBX_INIT_LINK 177 
#define  MBX_INIT_VFI 176 
#define  MBX_INIT_VPI 175 
#define  MBX_KILL_BOARD 174 
#define  MBX_LOAD_AREA 173 
#define  MBX_LOAD_EXP_ROM 172 
#define  MBX_LOAD_SM 171 
#define  MBX_PORT_CAPABILITIES 170 
#define  MBX_PORT_IOV_CONTROL 169 
#define  MBX_READ_CONFIG 168 
#define  MBX_READ_EVENT_LOG 167 
#define  MBX_READ_EVENT_LOG_STATUS 166 
#define  MBX_READ_LNK_STAT 165 
#define  MBX_READ_NV 164 
#define  MBX_READ_RCONFIG 163 
#define  MBX_READ_REV 162 
#define  MBX_READ_RPI 161 
#define  MBX_READ_RPI64 160 
#define  MBX_READ_SPARM 159 
#define  MBX_READ_SPARM64 158 
#define  MBX_READ_STATUS 157 
#define  MBX_READ_TOPOLOGY 156 
#define  MBX_READ_XRI 155 
#define  MBX_REG_FCFI 154 
#define  MBX_REG_LOGIN 153 
#define  MBX_REG_LOGIN64 152 
#define  MBX_REG_VFI 151 
#define  MBX_REG_VPI 150 
#define  MBX_RESET_RING 149 
#define  MBX_RESTART 148 
#define  MBX_RESUME_RPI 147 
#define  MBX_RUN_BIU_DIAG 146 
#define  MBX_RUN_BIU_DIAG64 145 
#define  MBX_RUN_DIAGS 144 
#define  MBX_RUN_PROGRAM 143 
#define  MBX_SECURITY_MGMT 142 
#define  MBX_SET_DEBUG 141 
#define  MBX_SET_MASK 140 
#define  MBX_SET_VARIABLE 139 
 int MBX_SHUTDOWN ; 
#define  MBX_SLI4_CONFIG 138 
#define  MBX_SLI4_REQ_FTRS 137 
#define  MBX_UNREG_D_ID 136 
#define  MBX_UNREG_FCFI 135 
#define  MBX_UNREG_LOGIN 134 
#define  MBX_UNREG_VFI 133 
#define  MBX_UNREG_VPI 132 
#define  MBX_UPDATE_CFG 131 
#define  MBX_WRITE_NV 130 
#define  MBX_WRITE_VPARMS 129 
#define  MBX_WRITE_WWN 128 

__attribute__((used)) static int
lpfc_sli_chk_mbx_command(uint8_t mbxCommand)
{
	uint8_t ret;

	switch (mbxCommand) {
	case MBX_LOAD_SM:
	case MBX_READ_NV:
	case MBX_WRITE_NV:
	case MBX_WRITE_VPARMS:
	case MBX_RUN_BIU_DIAG:
	case MBX_INIT_LINK:
	case MBX_DOWN_LINK:
	case MBX_CONFIG_LINK:
	case MBX_CONFIG_RING:
	case MBX_RESET_RING:
	case MBX_READ_CONFIG:
	case MBX_READ_RCONFIG:
	case MBX_READ_SPARM:
	case MBX_READ_STATUS:
	case MBX_READ_RPI:
	case MBX_READ_XRI:
	case MBX_READ_REV:
	case MBX_READ_LNK_STAT:
	case MBX_REG_LOGIN:
	case MBX_UNREG_LOGIN:
	case MBX_CLEAR_LA:
	case MBX_DUMP_MEMORY:
	case MBX_DUMP_CONTEXT:
	case MBX_RUN_DIAGS:
	case MBX_RESTART:
	case MBX_UPDATE_CFG:
	case MBX_DOWN_LOAD:
	case MBX_DEL_LD_ENTRY:
	case MBX_RUN_PROGRAM:
	case MBX_SET_MASK:
	case MBX_SET_VARIABLE:
	case MBX_UNREG_D_ID:
	case MBX_KILL_BOARD:
	case MBX_CONFIG_FARP:
	case MBX_BEACON:
	case MBX_LOAD_AREA:
	case MBX_RUN_BIU_DIAG64:
	case MBX_CONFIG_PORT:
	case MBX_READ_SPARM64:
	case MBX_READ_RPI64:
	case MBX_REG_LOGIN64:
	case MBX_READ_TOPOLOGY:
	case MBX_WRITE_WWN:
	case MBX_SET_DEBUG:
	case MBX_LOAD_EXP_ROM:
	case MBX_ASYNCEVT_ENABLE:
	case MBX_REG_VPI:
	case MBX_UNREG_VPI:
	case MBX_HEARTBEAT:
	case MBX_PORT_CAPABILITIES:
	case MBX_PORT_IOV_CONTROL:
	case MBX_SLI4_CONFIG:
	case MBX_SLI4_REQ_FTRS:
	case MBX_REG_FCFI:
	case MBX_UNREG_FCFI:
	case MBX_REG_VFI:
	case MBX_UNREG_VFI:
	case MBX_INIT_VPI:
	case MBX_INIT_VFI:
	case MBX_RESUME_RPI:
	case MBX_READ_EVENT_LOG_STATUS:
	case MBX_READ_EVENT_LOG:
	case MBX_SECURITY_MGMT:
	case MBX_AUTH_PORT:
	case MBX_ACCESS_VDATA:
		ret = mbxCommand;
		break;
	default:
		ret = MBX_SHUTDOWN;
		break;
	}
	return ret;
}