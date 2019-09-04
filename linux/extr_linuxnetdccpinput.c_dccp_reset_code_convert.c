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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  const u16 ;

/* Variables and functions */
 size_t const DCCP_MAX_RESET_CODES ; 
#define  DCCP_RESET_CODE_ABORTED 148 
#define  DCCP_RESET_CODE_AGGRESSION_PENALTY 147 
#define  DCCP_RESET_CODE_BAD_INIT_COOKIE 146 
#define  DCCP_RESET_CODE_BAD_SERVICE_CODE 145 
#define  DCCP_RESET_CODE_CLOSED 144 
#define  DCCP_RESET_CODE_CONNECTION_REFUSED 143 
#define  DCCP_RESET_CODE_MANDATORY_ERROR 142 
#define  DCCP_RESET_CODE_NO_CONNECTION 141 
#define  DCCP_RESET_CODE_OPTION_ERROR 140 
#define  DCCP_RESET_CODE_PACKET_ERROR 139 
#define  DCCP_RESET_CODE_TOO_BUSY 138 
#define  DCCP_RESET_CODE_UNSPECIFIED 137 
#define  EBADR 136 
#define  EBADRQC 135 
#define  ECONNREFUSED 134 
#define  ECONNRESET 133 
#define  EDQUOT 132 
#define  EILSEQ 131 
#define  ENOMSG 130 
#define  EOPNOTSUPP 129 
#define  EUSERS 128 

__attribute__((used)) static u16 dccp_reset_code_convert(const u8 code)
{
	static const u16 error_code[] = {
	[DCCP_RESET_CODE_CLOSED]	     = 0,	/* normal termination */
	[DCCP_RESET_CODE_UNSPECIFIED]	     = 0,	/* nothing known */
	[DCCP_RESET_CODE_ABORTED]	     = ECONNRESET,

	[DCCP_RESET_CODE_NO_CONNECTION]	     = ECONNREFUSED,
	[DCCP_RESET_CODE_CONNECTION_REFUSED] = ECONNREFUSED,
	[DCCP_RESET_CODE_TOO_BUSY]	     = EUSERS,
	[DCCP_RESET_CODE_AGGRESSION_PENALTY] = EDQUOT,

	[DCCP_RESET_CODE_PACKET_ERROR]	     = ENOMSG,
	[DCCP_RESET_CODE_BAD_INIT_COOKIE]    = EBADR,
	[DCCP_RESET_CODE_BAD_SERVICE_CODE]   = EBADRQC,
	[DCCP_RESET_CODE_OPTION_ERROR]	     = EILSEQ,
	[DCCP_RESET_CODE_MANDATORY_ERROR]    = EOPNOTSUPP,
	};

	return code >= DCCP_MAX_RESET_CODES ? 0 : error_code[code];
}