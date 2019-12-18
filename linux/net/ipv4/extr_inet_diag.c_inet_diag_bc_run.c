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
typedef  int /*<<< orphan*/  u32 ;
struct nlattr {int dummy; } ;
struct inet_diag_markcond {int mask; int mark; } ;
struct inet_diag_hostcond {int port; int /*<<< orphan*/  prefix_len; int /*<<< orphan*/  addr; int /*<<< orphan*/  family; } ;
struct inet_diag_entry {int sport; int dport; int userlocks; int mark; int /*<<< orphan*/  ifindex; int /*<<< orphan*/  family; int /*<<< orphan*/ * daddr; int /*<<< orphan*/ * saddr; } ;
struct inet_diag_bc_op {int code; int no; scalar_t__ yes; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  AF_UNSPEC ; 
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
 int SOCK_BINDPORT_LOCK ; 
 int /*<<< orphan*/  bitstring_match (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const htonl (int) ; 
 void* nla_data (struct nlattr const*) ; 
 int nla_len (struct nlattr const*) ; 

__attribute__((used)) static int inet_diag_bc_run(const struct nlattr *_bc,
			    const struct inet_diag_entry *entry)
{
	const void *bc = nla_data(_bc);
	int len = nla_len(_bc);

	while (len > 0) {
		int yes = 1;
		const struct inet_diag_bc_op *op = bc;

		switch (op->code) {
		case INET_DIAG_BC_NOP:
			break;
		case INET_DIAG_BC_JMP:
			yes = 0;
			break;
		case INET_DIAG_BC_S_EQ:
			yes = entry->sport == op[1].no;
			break;
		case INET_DIAG_BC_S_GE:
			yes = entry->sport >= op[1].no;
			break;
		case INET_DIAG_BC_S_LE:
			yes = entry->sport <= op[1].no;
			break;
		case INET_DIAG_BC_D_EQ:
			yes = entry->dport == op[1].no;
			break;
		case INET_DIAG_BC_D_GE:
			yes = entry->dport >= op[1].no;
			break;
		case INET_DIAG_BC_D_LE:
			yes = entry->dport <= op[1].no;
			break;
		case INET_DIAG_BC_AUTO:
			yes = !(entry->userlocks & SOCK_BINDPORT_LOCK);
			break;
		case INET_DIAG_BC_S_COND:
		case INET_DIAG_BC_D_COND: {
			const struct inet_diag_hostcond *cond;
			const __be32 *addr;

			cond = (const struct inet_diag_hostcond *)(op + 1);
			if (cond->port != -1 &&
			    cond->port != (op->code == INET_DIAG_BC_S_COND ?
					     entry->sport : entry->dport)) {
				yes = 0;
				break;
			}

			if (op->code == INET_DIAG_BC_S_COND)
				addr = entry->saddr;
			else
				addr = entry->daddr;

			if (cond->family != AF_UNSPEC &&
			    cond->family != entry->family) {
				if (entry->family == AF_INET6 &&
				    cond->family == AF_INET) {
					if (addr[0] == 0 && addr[1] == 0 &&
					    addr[2] == htonl(0xffff) &&
					    bitstring_match(addr + 3,
							    cond->addr,
							    cond->prefix_len))
						break;
				}
				yes = 0;
				break;
			}

			if (cond->prefix_len == 0)
				break;
			if (bitstring_match(addr, cond->addr,
					    cond->prefix_len))
				break;
			yes = 0;
			break;
		}
		case INET_DIAG_BC_DEV_COND: {
			u32 ifindex;

			ifindex = *((const u32 *)(op + 1));
			if (ifindex != entry->ifindex)
				yes = 0;
			break;
		}
		case INET_DIAG_BC_MARK_COND: {
			struct inet_diag_markcond *cond;

			cond = (struct inet_diag_markcond *)(op + 1);
			if ((entry->mark & cond->mask) != cond->mark)
				yes = 0;
			break;
		}
		}

		if (yes) {
			len -= op->yes;
			bc += op->yes;
		} else {
			len -= op->no;
			bc += op->no;
		}
	}
	return len == 0;
}