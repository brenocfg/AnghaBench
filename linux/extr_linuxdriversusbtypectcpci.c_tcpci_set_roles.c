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
struct tcpci {int /*<<< orphan*/  regmap; } ;
struct tcpc_dev {int dummy; } ;
typedef  enum typec_role { ____Placeholder_typec_role } typec_role ;
typedef  enum typec_data_role { ____Placeholder_typec_data_role } typec_data_role ;

/* Variables and functions */
 unsigned int PD_REV20 ; 
 int /*<<< orphan*/  TCPC_MSG_HDR_INFO ; 
 unsigned int TCPC_MSG_HDR_INFO_DATA_ROLE ; 
 unsigned int TCPC_MSG_HDR_INFO_PWR_ROLE ; 
 unsigned int TCPC_MSG_HDR_INFO_REV_SHIFT ; 
 int TYPEC_HOST ; 
 int TYPEC_SOURCE ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct tcpci* tcpc_to_tcpci (struct tcpc_dev*) ; 

__attribute__((used)) static int tcpci_set_roles(struct tcpc_dev *tcpc, bool attached,
			   enum typec_role role, enum typec_data_role data)
{
	struct tcpci *tcpci = tcpc_to_tcpci(tcpc);
	unsigned int reg;
	int ret;

	reg = PD_REV20 << TCPC_MSG_HDR_INFO_REV_SHIFT;
	if (role == TYPEC_SOURCE)
		reg |= TCPC_MSG_HDR_INFO_PWR_ROLE;
	if (data == TYPEC_HOST)
		reg |= TCPC_MSG_HDR_INFO_DATA_ROLE;
	ret = regmap_write(tcpci->regmap, TCPC_MSG_HDR_INFO, reg);
	if (ret < 0)
		return ret;

	return 0;
}