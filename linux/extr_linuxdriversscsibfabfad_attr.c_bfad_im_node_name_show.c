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
typedef  int /*<<< orphan*/  u64 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct bfad_port_s {int /*<<< orphan*/  fcs_port; } ;
struct bfad_im_port_s {struct bfad_port_s* port; } ;
struct Scsi_Host {scalar_t__* hostdata; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  bfa_fcs_lport_get_nwwn (int /*<<< orphan*/ ) ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
bfad_im_node_name_show(struct device *dev, struct device_attribute *attr,
				 char *buf)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct bfad_im_port_s *im_port =
			(struct bfad_im_port_s *) shost->hostdata[0];
	struct bfad_port_s    *port = im_port->port;
	u64        nwwn;

	nwwn = bfa_fcs_lport_get_nwwn(port->fcs_port);
	return snprintf(buf, PAGE_SIZE, "0x%llx\n", cpu_to_be64(nwwn));
}