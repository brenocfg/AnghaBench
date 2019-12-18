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
typedef  int RPC_STATUS ;
typedef  int NCA_STATUS ;

/* Variables and functions */
#define  ERROR_INVALID_HANDLE 152 
#define  ERROR_OUTOFMEMORY 151 
 int NCA_S_COMM_FAILURE ; 
 int NCA_S_FAULT_CANCEL ; 
 int NCA_S_FAULT_CONTEXT_MISMATCH ; 
 int NCA_S_FAULT_FP_DIV_ZERO ; 
 int NCA_S_FAULT_FP_ERROR ; 
 int NCA_S_FAULT_FP_OVERFLOW ; 
 int NCA_S_FAULT_FP_UNDERFLOW ; 
 int NCA_S_FAULT_INT_DIV_BY_ZERO ; 
 int NCA_S_FAULT_INT_OVERFLOW ; 
 int NCA_S_FAULT_INVALID_BOUND ; 
 int NCA_S_FAULT_INVALID_TAG ; 
 int NCA_S_FAULT_PIPE_CLOSED ; 
 int NCA_S_FAULT_PIPE_DISCIPLINE ; 
 int NCA_S_FAULT_PIPE_EMPTY ; 
 int NCA_S_FAULT_PIPE_ORDER ; 
 int NCA_S_FAULT_REMOTE_NO_MEMORY ; 
 int NCA_S_FAULT_UNSPEC ; 
 int NCA_S_MANAGER_NOT_ENTERED ; 
 int NCA_S_OP_RNG_ERROR ; 
 int NCA_S_PROTO_ERROR ; 
 int NCA_S_SERVER_TOO_BUSY ; 
 int NCA_S_UNK_IF ; 
 int NCA_S_UNSUPPORTED_TYPE ; 
#define  RPC_S_CALL_CANCELLED 150 
#define  RPC_S_CALL_FAILED 149 
#define  RPC_S_CALL_FAILED_DNE 148 
#define  RPC_S_COMM_FAILURE 147 
#define  RPC_S_INVALID_BOUND 146 
#define  RPC_S_INVALID_TAG 145 
#define  RPC_S_NOT_LISTENING 144 
#define  RPC_S_PROCNUM_OUT_OF_RANGE 143 
#define  RPC_S_PROTOCOL_ERROR 142 
#define  RPC_S_SERVER_TOO_BUSY 141 
#define  RPC_S_UNKNOWN_IF 140 
#define  RPC_S_UNSUPPORTED_TYPE 139 
#define  RPC_X_PIPE_CLOSED 138 
#define  RPC_X_PIPE_DISCIPLINE_ERROR 137 
#define  RPC_X_PIPE_EMPTY 136 
#define  RPC_X_SS_HANDLES_MISMATCH 135 
#define  RPC_X_WRONG_PIPE_ORDER 134 
#define  STATUS_FLOAT_DIVIDE_BY_ZERO 133 
#define  STATUS_FLOAT_INVALID_OPERATION 132 
#define  STATUS_FLOAT_OVERFLOW 131 
#define  STATUS_FLOAT_UNDERFLOW 130 
#define  STATUS_INTEGER_DIVIDE_BY_ZERO 129 
#define  STATUS_INTEGER_OVERFLOW 128 

NCA_STATUS RPC2NCA_STATUS(RPC_STATUS status)
{
    switch (status)
    {
    case ERROR_INVALID_HANDLE:              return NCA_S_FAULT_CONTEXT_MISMATCH;
    case ERROR_OUTOFMEMORY:                 return NCA_S_FAULT_REMOTE_NO_MEMORY;
    case RPC_S_NOT_LISTENING:               return NCA_S_SERVER_TOO_BUSY;
    case RPC_S_UNKNOWN_IF:                  return NCA_S_UNK_IF;
    case RPC_S_SERVER_TOO_BUSY:             return NCA_S_SERVER_TOO_BUSY;
    case RPC_S_CALL_FAILED:                 return NCA_S_FAULT_UNSPEC;
    case RPC_S_CALL_FAILED_DNE:             return NCA_S_MANAGER_NOT_ENTERED;
    case RPC_S_PROTOCOL_ERROR:              return NCA_S_PROTO_ERROR;
    case RPC_S_UNSUPPORTED_TYPE:            return NCA_S_UNSUPPORTED_TYPE;
    case RPC_S_INVALID_TAG:                 return NCA_S_FAULT_INVALID_TAG;
    case RPC_S_INVALID_BOUND:               return NCA_S_FAULT_INVALID_BOUND;
    case RPC_S_PROCNUM_OUT_OF_RANGE:        return NCA_S_OP_RNG_ERROR;
    case RPC_X_SS_HANDLES_MISMATCH:         return NCA_S_FAULT_CONTEXT_MISMATCH;
    case RPC_S_CALL_CANCELLED:              return NCA_S_FAULT_CANCEL;
    case RPC_S_COMM_FAILURE:                return NCA_S_COMM_FAILURE;
    case RPC_X_WRONG_PIPE_ORDER:            return NCA_S_FAULT_PIPE_ORDER;
    case RPC_X_PIPE_CLOSED:                 return NCA_S_FAULT_PIPE_CLOSED;
    case RPC_X_PIPE_DISCIPLINE_ERROR:       return NCA_S_FAULT_PIPE_DISCIPLINE;
    case RPC_X_PIPE_EMPTY:                  return NCA_S_FAULT_PIPE_EMPTY;
    case STATUS_FLOAT_DIVIDE_BY_ZERO:       return NCA_S_FAULT_FP_DIV_ZERO;
    case STATUS_FLOAT_INVALID_OPERATION:    return NCA_S_FAULT_FP_ERROR;
    case STATUS_FLOAT_OVERFLOW:             return NCA_S_FAULT_FP_OVERFLOW;
    case STATUS_FLOAT_UNDERFLOW:            return NCA_S_FAULT_FP_UNDERFLOW;
    case STATUS_INTEGER_DIVIDE_BY_ZERO:     return NCA_S_FAULT_INT_DIV_BY_ZERO;
    case STATUS_INTEGER_OVERFLOW:           return NCA_S_FAULT_INT_OVERFLOW;
    default:                                return status;
    }
}