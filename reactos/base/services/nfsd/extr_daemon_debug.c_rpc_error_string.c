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

/* Variables and functions */
#define  RPC_AUTHERROR 141 
#define  RPC_CANTDECODEARGS 140 
#define  RPC_CANTDECODERES 139 
#define  RPC_CANTENCODEARGS 138 
#define  RPC_CANTRECV 137 
#define  RPC_CANTSEND 136 
#define  RPC_INTR 135 
#define  RPC_PROCUNAVAIL 134 
#define  RPC_PROGUNAVAIL 133 
#define  RPC_PROGVERSMISMATCH 132 
#define  RPC_SYSTEMERROR 131 
#define  RPC_TIMEDOUT 130 
#define  RPC_UDERROR 129 
#define  RPC_VERSMISMATCH 128 

const char* rpc_error_string(int status)
{
    switch (status)
    {
    case RPC_CANTENCODEARGS: return "RPC_CANTENCODEARGS";
    case RPC_CANTDECODERES: return "RPC_CANTDECODERES";
    case RPC_CANTSEND: return "RPC_CANTSEND";
    case RPC_CANTRECV: return "RPC_CANTRECV";
    case RPC_TIMEDOUT: return "RPC_TIMEDOUT";
    case RPC_INTR: return "RPC_INTR";
    case RPC_UDERROR: return "RPC_UDERROR";
    case RPC_VERSMISMATCH: return "RPC_VERSMISMATCH";
    case RPC_AUTHERROR: return "RPC_AUTHERROR";
    case RPC_PROGUNAVAIL: return "RPC_PROGUNAVAIL";
    case RPC_PROGVERSMISMATCH: return "RPC_PROGVERSMISMATCH";
    case RPC_PROCUNAVAIL: return "RPC_PROCUNAVAIL";
    case RPC_CANTDECODEARGS: return "RPC_CANTDECODEARGS";
    case RPC_SYSTEMERROR: return "RPC_SYSTEMERROR";
    default: return "invalid rpc error code";
    }
}