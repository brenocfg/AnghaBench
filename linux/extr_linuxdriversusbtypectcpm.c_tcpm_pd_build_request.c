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
struct tcpm_port {unsigned int operating_snk_mw; scalar_t__ vconn_role; unsigned int current_limit; unsigned int supply_voltage; int /*<<< orphan*/  polarity; int /*<<< orphan*/  vbus_source; int /*<<< orphan*/  cc2; int /*<<< orphan*/  cc1; int /*<<< orphan*/  cc_req; int /*<<< orphan*/ * snk_pdo; int /*<<< orphan*/ * source_caps; } ;
typedef  enum pd_pdo_type { ____Placeholder_pd_pdo_type } pd_pdo_type ;

/* Variables and functions */
 int EINVAL ; 
#define  PDO_TYPE_BATT 130 
#define  PDO_TYPE_FIXED 129 
#define  PDO_TYPE_VAR 128 
 int /*<<< orphan*/  RDO_BATT (int,unsigned int,unsigned int,unsigned int) ; 
 unsigned int RDO_CAP_MISMATCH ; 
 int /*<<< orphan*/  RDO_FIXED (int,unsigned int,unsigned int,unsigned int) ; 
 unsigned int RDO_NO_SUSPEND ; 
 unsigned int RDO_USB_COMM ; 
 scalar_t__ TYPEC_SOURCE ; 
 unsigned int min_current (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int min_power (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int pdo_fixed_voltage (int /*<<< orphan*/ ) ; 
 unsigned int pdo_max_current (int /*<<< orphan*/ ) ; 
 unsigned int pdo_max_power (int /*<<< orphan*/ ) ; 
 unsigned int pdo_min_voltage (int /*<<< orphan*/ ) ; 
 int pdo_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpm_log (struct tcpm_port*,char*,...) ; 
 int tcpm_pd_select_pdo (struct tcpm_port*,int*,int*) ; 

__attribute__((used)) static int tcpm_pd_build_request(struct tcpm_port *port, u32 *rdo)
{
	unsigned int mv, ma, mw, flags;
	unsigned int max_ma, max_mw;
	enum pd_pdo_type type;
	u32 pdo, matching_snk_pdo;
	int src_pdo_index = 0;
	int snk_pdo_index = 0;
	int ret;

	ret = tcpm_pd_select_pdo(port, &snk_pdo_index, &src_pdo_index);
	if (ret < 0)
		return ret;

	pdo = port->source_caps[src_pdo_index];
	matching_snk_pdo = port->snk_pdo[snk_pdo_index];
	type = pdo_type(pdo);

	switch (type) {
	case PDO_TYPE_FIXED:
		mv = pdo_fixed_voltage(pdo);
		break;
	case PDO_TYPE_BATT:
	case PDO_TYPE_VAR:
		mv = pdo_min_voltage(pdo);
		break;
	default:
		tcpm_log(port, "Invalid PDO selected!");
		return -EINVAL;
	}

	/* Select maximum available current within the sink pdo's limit */
	if (type == PDO_TYPE_BATT) {
		mw = min_power(pdo, matching_snk_pdo);
		ma = 1000 * mw / mv;
	} else {
		ma = min_current(pdo, matching_snk_pdo);
		mw = ma * mv / 1000;
	}

	flags = RDO_USB_COMM | RDO_NO_SUSPEND;

	/* Set mismatch bit if offered power is less than operating power */
	max_ma = ma;
	max_mw = mw;
	if (mw < port->operating_snk_mw) {
		flags |= RDO_CAP_MISMATCH;
		if (type == PDO_TYPE_BATT &&
		    (pdo_max_power(matching_snk_pdo) > pdo_max_power(pdo)))
			max_mw = pdo_max_power(matching_snk_pdo);
		else if (pdo_max_current(matching_snk_pdo) >
			 pdo_max_current(pdo))
			max_ma = pdo_max_current(matching_snk_pdo);
	}

	tcpm_log(port, "cc=%d cc1=%d cc2=%d vbus=%d vconn=%s polarity=%d",
		 port->cc_req, port->cc1, port->cc2, port->vbus_source,
		 port->vconn_role == TYPEC_SOURCE ? "source" : "sink",
		 port->polarity);

	if (type == PDO_TYPE_BATT) {
		*rdo = RDO_BATT(src_pdo_index + 1, mw, max_mw, flags);

		tcpm_log(port, "Requesting PDO %d: %u mV, %u mW%s",
			 src_pdo_index, mv, mw,
			 flags & RDO_CAP_MISMATCH ? " [mismatch]" : "");
	} else {
		*rdo = RDO_FIXED(src_pdo_index + 1, ma, max_ma, flags);

		tcpm_log(port, "Requesting PDO %d: %u mV, %u mA%s",
			 src_pdo_index, mv, ma,
			 flags & RDO_CAP_MISMATCH ? " [mismatch]" : "");
	}

	port->current_limit = ma;
	port->supply_voltage = mv;

	return 0;
}