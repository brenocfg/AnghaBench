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
typedef  int u32 ;
typedef  void* u16 ;
struct pd_mode_data {scalar_t__ nsvids; void** svids; } ;
struct tcpm_port {struct pd_mode_data mode_data; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 scalar_t__ SVID_DISCOVERY_MAX ; 
 int le32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  tcpm_log (struct tcpm_port*,char*,scalar_t__,...) ; 

__attribute__((used)) static bool svdm_consume_svids(struct tcpm_port *port, const __le32 *payload,
			       int cnt)
{
	struct pd_mode_data *pmdata = &port->mode_data;
	int i;

	for (i = 1; i < cnt; i++) {
		u32 p = le32_to_cpu(payload[i]);
		u16 svid;

		svid = (p >> 16) & 0xffff;
		if (!svid)
			return false;

		if (pmdata->nsvids >= SVID_DISCOVERY_MAX)
			goto abort;

		pmdata->svids[pmdata->nsvids++] = svid;
		tcpm_log(port, "SVID %d: 0x%x", pmdata->nsvids, svid);

		svid = p & 0xffff;
		if (!svid)
			return false;

		if (pmdata->nsvids >= SVID_DISCOVERY_MAX)
			goto abort;

		pmdata->svids[pmdata->nsvids++] = svid;
		tcpm_log(port, "SVID %d: 0x%x", pmdata->nsvids, svid);
	}
	return true;
abort:
	tcpm_log(port, "SVID_DISCOVERY_MAX(%d) too low!", SVID_DISCOVERY_MAX);
	return false;
}