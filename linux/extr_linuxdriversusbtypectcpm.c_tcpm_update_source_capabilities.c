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
struct tcpm_port {int state; int /*<<< orphan*/  lock; int /*<<< orphan*/  src_pdo; int /*<<< orphan*/  nr_src_pdo; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SRC_ATTACH_WAIT 134 
#define  SRC_NEGOTIATE_CAPABILITIES 133 
#define  SRC_READY 132 
#define  SRC_SEND_CAPABILITIES 131 
#define  SRC_TRYWAIT 130 
#define  SRC_UNATTACHED 129 
#define  SRC_WAIT_NEW_CAPABILITIES 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcpm_copy_pdos (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  tcpm_rp_cc (struct tcpm_port*) ; 
 int /*<<< orphan*/  tcpm_set_cc (struct tcpm_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpm_set_state (struct tcpm_port*,int const,int /*<<< orphan*/ ) ; 
 scalar_t__ tcpm_validate_caps (struct tcpm_port*,int /*<<< orphan*/  const*,unsigned int) ; 

int tcpm_update_source_capabilities(struct tcpm_port *port, const u32 *pdo,
				    unsigned int nr_pdo)
{
	if (tcpm_validate_caps(port, pdo, nr_pdo))
		return -EINVAL;

	mutex_lock(&port->lock);
	port->nr_src_pdo = tcpm_copy_pdos(port->src_pdo, pdo, nr_pdo);
	switch (port->state) {
	case SRC_UNATTACHED:
	case SRC_ATTACH_WAIT:
	case SRC_TRYWAIT:
		tcpm_set_cc(port, tcpm_rp_cc(port));
		break;
	case SRC_SEND_CAPABILITIES:
	case SRC_NEGOTIATE_CAPABILITIES:
	case SRC_READY:
	case SRC_WAIT_NEW_CAPABILITIES:
		tcpm_set_cc(port, tcpm_rp_cc(port));
		tcpm_set_state(port, SRC_SEND_CAPABILITIES, 0);
		break;
	default:
		break;
	}
	mutex_unlock(&port->lock);
	return 0;
}