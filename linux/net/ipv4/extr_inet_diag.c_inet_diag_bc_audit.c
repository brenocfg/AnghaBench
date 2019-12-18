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
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct inet_diag_bc_op {int code; int no; int yes; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EINVAL ; 
 int EPERM ; 
#define  INET_DIAG_BC_AUTO 140 
#define  INET_DIAG_BC_DEV_COND 139 
#define  INET_DIAG_BC_D_COND 138 
#define  INET_DIAG_BC_D_EQ 137 
#define  INET_DIAG_BC_D_GE 136 
#define  INET_DIAG_BC_D_LE 135 
#define  INET_DIAG_BC_JMP 134 
#define  INET_DIAG_BC_MARK_COND 133 
#define  INET_DIAG_BC_NOP 132 
#define  INET_DIAG_BC_S_COND 131 
#define  INET_DIAG_BC_S_EQ 130 
#define  INET_DIAG_BC_S_GE 129 
#define  INET_DIAG_BC_S_LE 128 
 int netlink_net_capable (struct sk_buff const*,int /*<<< orphan*/ ) ; 
 void* nla_data (struct nlattr const*) ; 
 int nla_len (struct nlattr const*) ; 
 int /*<<< orphan*/  valid_cc (void const*,int,int) ; 
 int /*<<< orphan*/  valid_devcond (void const*,int,int*) ; 
 int /*<<< orphan*/  valid_hostcond (void const*,int,int*) ; 
 int /*<<< orphan*/  valid_markcond (void const*,int,int*) ; 
 int /*<<< orphan*/  valid_port_comparison (void const*,int,int*) ; 

__attribute__((used)) static int inet_diag_bc_audit(const struct nlattr *attr,
			      const struct sk_buff *skb)
{
	bool net_admin = netlink_net_capable(skb, CAP_NET_ADMIN);
	const void *bytecode, *bc;
	int bytecode_len, len;

	if (!attr || nla_len(attr) < sizeof(struct inet_diag_bc_op))
		return -EINVAL;

	bytecode = bc = nla_data(attr);
	len = bytecode_len = nla_len(attr);

	while (len > 0) {
		int min_len = sizeof(struct inet_diag_bc_op);
		const struct inet_diag_bc_op *op = bc;

		switch (op->code) {
		case INET_DIAG_BC_S_COND:
		case INET_DIAG_BC_D_COND:
			if (!valid_hostcond(bc, len, &min_len))
				return -EINVAL;
			break;
		case INET_DIAG_BC_DEV_COND:
			if (!valid_devcond(bc, len, &min_len))
				return -EINVAL;
			break;
		case INET_DIAG_BC_S_EQ:
		case INET_DIAG_BC_S_GE:
		case INET_DIAG_BC_S_LE:
		case INET_DIAG_BC_D_EQ:
		case INET_DIAG_BC_D_GE:
		case INET_DIAG_BC_D_LE:
			if (!valid_port_comparison(bc, len, &min_len))
				return -EINVAL;
			break;
		case INET_DIAG_BC_MARK_COND:
			if (!net_admin)
				return -EPERM;
			if (!valid_markcond(bc, len, &min_len))
				return -EINVAL;
			break;
		case INET_DIAG_BC_AUTO:
		case INET_DIAG_BC_JMP:
		case INET_DIAG_BC_NOP:
			break;
		default:
			return -EINVAL;
		}

		if (op->code != INET_DIAG_BC_NOP) {
			if (op->no < min_len || op->no > len + 4 || op->no & 3)
				return -EINVAL;
			if (op->no < len &&
			    !valid_cc(bytecode, bytecode_len, len - op->no))
				return -EINVAL;
		}

		if (op->yes < min_len || op->yes > len + 4 || op->yes & 3)
			return -EINVAL;
		bc  += op->yes;
		len -= op->yes;
	}
	return len == 0 ? 0 : -EINVAL;
}