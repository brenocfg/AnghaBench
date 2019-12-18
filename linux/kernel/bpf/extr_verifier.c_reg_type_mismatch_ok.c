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
typedef  enum bpf_reg_type { ____Placeholder_bpf_reg_type } bpf_reg_type ;

/* Variables and functions */
#define  PTR_TO_CTX 135 
#define  PTR_TO_SOCKET 134 
#define  PTR_TO_SOCKET_OR_NULL 133 
#define  PTR_TO_SOCK_COMMON 132 
#define  PTR_TO_SOCK_COMMON_OR_NULL 131 
#define  PTR_TO_TCP_SOCK 130 
#define  PTR_TO_TCP_SOCK_OR_NULL 129 
#define  PTR_TO_XDP_SOCK 128 

__attribute__((used)) static bool reg_type_mismatch_ok(enum bpf_reg_type type)
{
	switch (type) {
	case PTR_TO_CTX:
	case PTR_TO_SOCKET:
	case PTR_TO_SOCKET_OR_NULL:
	case PTR_TO_SOCK_COMMON:
	case PTR_TO_SOCK_COMMON_OR_NULL:
	case PTR_TO_TCP_SOCK:
	case PTR_TO_TCP_SOCK_OR_NULL:
	case PTR_TO_XDP_SOCK:
		return false;
	default:
		return true;
	}
}