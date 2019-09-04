#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  bport; } ;
struct TYPE_5__ {TYPE_4__ fabric; } ;
struct bfad_s {TYPE_1__ bfa_fcs; } ;
struct bfad_im_port_s {struct bfad_s* bfad; } ;
struct TYPE_6__ {int /*<<< orphan*/  symname; } ;
struct TYPE_7__ {TYPE_2__ sym_name; } ;
struct bfa_lport_attr_s {TYPE_3__ port_cfg; } ;
struct Scsi_Host {scalar_t__* hostdata; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int BFA_SYMNAME_MAXLEN ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  bfa_fcs_lport_get_attr (int /*<<< orphan*/ *,struct bfa_lport_attr_s*) ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t
bfad_im_symbolic_name_show(struct device *dev, struct device_attribute *attr,
				 char *buf)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct bfad_im_port_s *im_port =
			(struct bfad_im_port_s *) shost->hostdata[0];
	struct bfad_s *bfad = im_port->bfad;
	struct bfa_lport_attr_s port_attr;
	char symname[BFA_SYMNAME_MAXLEN];

	bfa_fcs_lport_get_attr(&bfad->bfa_fcs.fabric.bport, &port_attr);
	strlcpy(symname, port_attr.port_cfg.sym_name.symname,
			BFA_SYMNAME_MAXLEN);
	return snprintf(buf, PAGE_SIZE, "%s\n", symname);
}