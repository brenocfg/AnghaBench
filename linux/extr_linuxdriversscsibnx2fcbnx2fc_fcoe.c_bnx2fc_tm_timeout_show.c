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
struct fcoe_port {struct bnx2fc_interface* priv; } ;
struct fc_lport {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct bnx2fc_interface {int tm_timeout; } ;
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct Scsi_Host* class_to_shost (struct device*) ; 
 struct fcoe_port* lport_priv (struct fc_lport*) ; 
 struct fc_lport* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static ssize_t
bnx2fc_tm_timeout_show(struct device *dev, struct device_attribute *attr,
	char *buf)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct fc_lport *lport = shost_priv(shost);
	struct fcoe_port *port = lport_priv(lport);
	struct bnx2fc_interface *interface = port->priv;

	sprintf(buf, "%u\n", interface->tm_timeout);
	return strlen(buf);
}