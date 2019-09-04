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
struct fc_rport {int port_id; scalar_t__ roles; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  FC_DIRSRVR_PORTID 132 
#define  FC_FABCTLR_PORTID 131 
#define  FC_FPORT_PORTID 130 
#define  FC_MGMTSRVR_PORTID 129 
 scalar_t__ FC_PORT_ROLE_UNKNOWN ; 
#define  FC_TIMESRVR_PORTID 128 
 int FC_WELLKNOWN_PORTID_MASK ; 
 int FC_WELLKNOWN_ROLE_MASK ; 
 int /*<<< orphan*/  get_fc_port_roles_names (scalar_t__,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 struct fc_rport* transport_class_to_rport (struct device*) ; 

__attribute__((used)) static ssize_t
show_fc_rport_roles (struct device *dev, struct device_attribute *attr,
		     char *buf)
{
	struct fc_rport *rport = transport_class_to_rport(dev);

	/* identify any roles that are port_id specific */
	if ((rport->port_id != -1) &&
	    (rport->port_id & FC_WELLKNOWN_PORTID_MASK) ==
					FC_WELLKNOWN_PORTID_MASK) {
		switch (rport->port_id & FC_WELLKNOWN_ROLE_MASK) {
		case FC_FPORT_PORTID:
			return snprintf(buf, 30, "Fabric Port\n");
		case FC_FABCTLR_PORTID:
			return snprintf(buf, 30, "Fabric Controller\n");
		case FC_DIRSRVR_PORTID:
			return snprintf(buf, 30, "Directory Server\n");
		case FC_TIMESRVR_PORTID:
			return snprintf(buf, 30, "Time Server\n");
		case FC_MGMTSRVR_PORTID:
			return snprintf(buf, 30, "Management Server\n");
		default:
			return snprintf(buf, 30, "Unknown Fabric Entity\n");
		}
	} else {
		if (rport->roles == FC_PORT_ROLE_UNKNOWN)
			return snprintf(buf, 20, "unknown\n");
		return get_fc_port_roles_names(rport->roles, buf);
	}
}