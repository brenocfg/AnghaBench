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
 int ERROR_INVALID_HANDLE ; 
 int ERROR_NOT_ENOUGH_SERVER_MEMORY ; 
 int ERROR_OUTOFMEMORY ; 
#define  NCA_S_BAD_ACTID 160 
#define  NCA_S_COMM_FAILURE 159 
#define  NCA_S_FAULT_ADDR_ERROR 158 
#define  NCA_S_FAULT_CANCEL 157 
#define  NCA_S_FAULT_CONTEXT_MISMATCH 156 
#define  NCA_S_FAULT_FP_DIV_ZERO 155 
#define  NCA_S_FAULT_FP_ERROR 154 
#define  NCA_S_FAULT_FP_OVERFLOW 153 
#define  NCA_S_FAULT_FP_UNDERFLOW 152 
#define  NCA_S_FAULT_ILL_INST 151 
#define  NCA_S_FAULT_INT_DIV_BY_ZERO 150 
#define  NCA_S_FAULT_INT_OVERFLOW 149 
#define  NCA_S_FAULT_INVALID_BOUND 148 
#define  NCA_S_FAULT_INVALID_TAG 147 
#define  NCA_S_FAULT_PIPE_CLOSED 146 
#define  NCA_S_FAULT_PIPE_COMM_ERROR 145 
#define  NCA_S_FAULT_PIPE_DISCIPLINE 144 
#define  NCA_S_FAULT_PIPE_EMPTY 143 
#define  NCA_S_FAULT_PIPE_MEMORY 142 
#define  NCA_S_FAULT_PIPE_ORDER 141 
#define  NCA_S_FAULT_REMOTE_NO_MEMORY 140 
#define  NCA_S_FAULT_UNSPEC 139 
#define  NCA_S_MANAGER_NOT_ENTERED 138 
#define  NCA_S_OP_RNG_ERROR 137 
#define  NCA_S_OUT_ARGS_TOO_BIG 136 
#define  NCA_S_PROTO_ERROR 135 
#define  NCA_S_RPC_VERSION_MISMATCH 134 
#define  NCA_S_SERVER_TOO_BUSY 133 
#define  NCA_S_UNK_IF 132 
#define  NCA_S_UNSPEC_REJECT 131 
#define  NCA_S_UNSUPPORTED_TYPE 130 
#define  NCA_S_WHO_ARE_YOU_FAILED 129 
#define  NCA_S_YOU_CRASHED 128 
 int RPC_S_ADDRESS_ERROR ; 
 int RPC_S_CALL_CANCELLED ; 
 int RPC_S_CALL_FAILED ; 
 int RPC_S_CALL_FAILED_DNE ; 
 int RPC_S_COMM_FAILURE ; 
 int RPC_S_FP_DIV_ZERO ; 
 int RPC_S_FP_OVERFLOW ; 
 int RPC_S_FP_UNDERFLOW ; 
 int RPC_S_INVALID_BOUND ; 
 int RPC_S_INVALID_TAG ; 
 int RPC_S_PROCNUM_OUT_OF_RANGE ; 
 int RPC_S_PROTOCOL_ERROR ; 
 int RPC_S_SERVER_TOO_BUSY ; 
 int RPC_S_UNKNOWN_IF ; 
 int RPC_S_UNSUPPORTED_TYPE ; 
 int RPC_S_ZERO_DIVIDE ; 
 int RPC_X_PIPE_CLOSED ; 
 int RPC_X_PIPE_DISCIPLINE_ERROR ; 
 int RPC_X_PIPE_EMPTY ; 
 int RPC_X_WRONG_PIPE_ORDER ; 

__attribute__((used)) static RPC_STATUS NCA2RPC_STATUS(NCA_STATUS status)
{
    switch (status)
    {
    case NCA_S_COMM_FAILURE:            return RPC_S_COMM_FAILURE;
    case NCA_S_OP_RNG_ERROR:            return RPC_S_PROCNUM_OUT_OF_RANGE;
    case NCA_S_UNK_IF:                  return RPC_S_UNKNOWN_IF;
    case NCA_S_YOU_CRASHED:             return RPC_S_CALL_FAILED;
    case NCA_S_PROTO_ERROR:             return RPC_S_PROTOCOL_ERROR;
    case NCA_S_OUT_ARGS_TOO_BIG:        return ERROR_NOT_ENOUGH_SERVER_MEMORY;
    case NCA_S_SERVER_TOO_BUSY:         return RPC_S_SERVER_TOO_BUSY;
    case NCA_S_UNSUPPORTED_TYPE:        return RPC_S_UNSUPPORTED_TYPE;
    case NCA_S_FAULT_INT_DIV_BY_ZERO:   return RPC_S_ZERO_DIVIDE;
    case NCA_S_FAULT_ADDR_ERROR:        return RPC_S_ADDRESS_ERROR;
    case NCA_S_FAULT_FP_DIV_ZERO:       return RPC_S_FP_DIV_ZERO;
    case NCA_S_FAULT_FP_UNDERFLOW:      return RPC_S_FP_UNDERFLOW;
    case NCA_S_FAULT_FP_OVERFLOW:       return RPC_S_FP_OVERFLOW;
    case NCA_S_FAULT_INVALID_TAG:       return RPC_S_INVALID_TAG;
    case NCA_S_FAULT_INVALID_BOUND:     return RPC_S_INVALID_BOUND;
    case NCA_S_RPC_VERSION_MISMATCH:    return RPC_S_PROTOCOL_ERROR;
    case NCA_S_UNSPEC_REJECT:           return RPC_S_CALL_FAILED_DNE;
    case NCA_S_BAD_ACTID:               return RPC_S_CALL_FAILED_DNE;
    case NCA_S_WHO_ARE_YOU_FAILED:      return RPC_S_CALL_FAILED;
    case NCA_S_MANAGER_NOT_ENTERED:     return RPC_S_CALL_FAILED_DNE;
    case NCA_S_FAULT_CANCEL:            return RPC_S_CALL_CANCELLED;
    case NCA_S_FAULT_ILL_INST:          return RPC_S_ADDRESS_ERROR;
    case NCA_S_FAULT_FP_ERROR:          return RPC_S_FP_OVERFLOW;
    case NCA_S_FAULT_INT_OVERFLOW:      return RPC_S_ADDRESS_ERROR;
    case NCA_S_FAULT_UNSPEC:            return RPC_S_CALL_FAILED;
    case NCA_S_FAULT_PIPE_EMPTY:        return RPC_X_PIPE_EMPTY;
    case NCA_S_FAULT_PIPE_CLOSED:       return RPC_X_PIPE_CLOSED;
    case NCA_S_FAULT_PIPE_ORDER:        return RPC_X_WRONG_PIPE_ORDER;
    case NCA_S_FAULT_PIPE_DISCIPLINE:   return RPC_X_PIPE_DISCIPLINE_ERROR;
    case NCA_S_FAULT_PIPE_COMM_ERROR:   return RPC_S_COMM_FAILURE;
    case NCA_S_FAULT_PIPE_MEMORY:       return ERROR_OUTOFMEMORY;
    case NCA_S_FAULT_CONTEXT_MISMATCH:  return ERROR_INVALID_HANDLE;
    case NCA_S_FAULT_REMOTE_NO_MEMORY:  return ERROR_NOT_ENOUGH_SERVER_MEMORY;
    default:                            return status;
    }
}