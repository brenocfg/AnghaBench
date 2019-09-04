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
struct qeth_ipaddr {int type; int proto; int /*<<< orphan*/  disp_flag; } ;
typedef  enum qeth_prot_versions { ____Placeholder_qeth_prot_versions } qeth_prot_versions ;
typedef  enum qeth_ip_types { ____Placeholder_qeth_ip_types } qeth_ip_types ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_DISP_ADDR_DO_NOTHING ; 
 int /*<<< orphan*/  memset (struct qeth_ipaddr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void qeth_l3_init_ipaddr(struct qeth_ipaddr *addr,
				       enum qeth_ip_types type,
				       enum qeth_prot_versions proto)
{
	memset(addr, 0, sizeof(*addr));
	addr->type = type;
	addr->proto = proto;
	addr->disp_flag = QETH_DISP_ADDR_DO_NOTHING;
}