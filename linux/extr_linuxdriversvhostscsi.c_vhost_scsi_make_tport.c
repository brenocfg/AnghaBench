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
struct se_wwn {int dummy; } ;
struct vhost_scsi_tport {struct se_wwn tport_wwn; int /*<<< orphan*/ * tport_name; int /*<<< orphan*/  tport_proto_id; int /*<<< orphan*/  tport_wwpn; } ;
struct target_fabric_configfs {int dummy; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct se_wwn* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SCSI_PROTOCOL_FCP ; 
 int /*<<< orphan*/  SCSI_PROTOCOL_ISCSI ; 
 int /*<<< orphan*/  SCSI_PROTOCOL_SAS ; 
 scalar_t__ VHOST_SCSI_NAMELEN ; 
 int /*<<< orphan*/  kfree (struct vhost_scsi_tport*) ; 
 struct vhost_scsi_tport* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,scalar_t__,char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 char* strstr (char const*,char*) ; 
 int /*<<< orphan*/  vhost_scsi_dump_proto_id (struct vhost_scsi_tport*) ; 

__attribute__((used)) static struct se_wwn *
vhost_scsi_make_tport(struct target_fabric_configfs *tf,
		     struct config_group *group,
		     const char *name)
{
	struct vhost_scsi_tport *tport;
	char *ptr;
	u64 wwpn = 0;
	int off = 0;

	/* if (vhost_scsi_parse_wwn(name, &wwpn, 1) < 0)
		return ERR_PTR(-EINVAL); */

	tport = kzalloc(sizeof(*tport), GFP_KERNEL);
	if (!tport) {
		pr_err("Unable to allocate struct vhost_scsi_tport");
		return ERR_PTR(-ENOMEM);
	}
	tport->tport_wwpn = wwpn;
	/*
	 * Determine the emulated Protocol Identifier and Target Port Name
	 * based on the incoming configfs directory name.
	 */
	ptr = strstr(name, "naa.");
	if (ptr) {
		tport->tport_proto_id = SCSI_PROTOCOL_SAS;
		goto check_len;
	}
	ptr = strstr(name, "fc.");
	if (ptr) {
		tport->tport_proto_id = SCSI_PROTOCOL_FCP;
		off = 3; /* Skip over "fc." */
		goto check_len;
	}
	ptr = strstr(name, "iqn.");
	if (ptr) {
		tport->tport_proto_id = SCSI_PROTOCOL_ISCSI;
		goto check_len;
	}

	pr_err("Unable to locate prefix for emulated Target Port:"
			" %s\n", name);
	kfree(tport);
	return ERR_PTR(-EINVAL);

check_len:
	if (strlen(name) >= VHOST_SCSI_NAMELEN) {
		pr_err("Emulated %s Address: %s, exceeds"
			" max: %d\n", name, vhost_scsi_dump_proto_id(tport),
			VHOST_SCSI_NAMELEN);
		kfree(tport);
		return ERR_PTR(-EINVAL);
	}
	snprintf(&tport->tport_name[0], VHOST_SCSI_NAMELEN, "%s", &name[off]);

	pr_debug("TCM_VHost_ConfigFS: Allocated emulated Target"
		" %s Address: %s\n", vhost_scsi_dump_proto_id(tport), name);

	return &tport->tport_wwn;
}