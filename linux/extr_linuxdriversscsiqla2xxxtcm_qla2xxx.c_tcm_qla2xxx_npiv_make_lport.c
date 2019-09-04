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
typedef  void* u64 ;
struct se_wwn {int dummy; } ;
struct tcm_qla2xxx_lport {int /*<<< orphan*/  lport_fcport_map; int /*<<< orphan*/  lport_loopid_map; struct se_wwn lport_wwn; int /*<<< orphan*/  lport_naa_name; void* lport_npiv_wwnn; void* lport_npiv_wwpn; } ;
struct target_fabric_configfs {int dummy; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct se_wwn* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  btree_destroy32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tcm_qla2xxx_lport*) ; 
 struct tcm_qla2xxx_lport* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int qlt_lport_register (struct tcm_qla2xxx_lport*,void*,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strlen (char*) ; 
 int tcm_qla2xxx_init_lport (struct tcm_qla2xxx_lport*) ; 
 int /*<<< orphan*/  tcm_qla2xxx_lport_register_npiv_cb ; 
 scalar_t__ tcm_qla2xxx_npiv_parse_wwn (char*,scalar_t__,void**,void**) ; 
 scalar_t__ tcm_qla2xxx_parse_wwn (char*,void**,int) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct se_wwn *tcm_qla2xxx_npiv_make_lport(
	struct target_fabric_configfs *tf,
	struct config_group *group,
	const char *name)
{
	struct tcm_qla2xxx_lport *lport;
	u64 phys_wwpn, npiv_wwpn, npiv_wwnn;
	char *p, tmp[128];
	int ret;

	snprintf(tmp, 128, "%s", name);

	p = strchr(tmp, '@');
	if (!p) {
		pr_err("Unable to locate NPIV '@' separator\n");
		return ERR_PTR(-EINVAL);
	}
	*p++ = '\0';

	if (tcm_qla2xxx_parse_wwn(tmp, &phys_wwpn, 1) < 0)
		return ERR_PTR(-EINVAL);

	if (tcm_qla2xxx_npiv_parse_wwn(p, strlen(p)+1,
				       &npiv_wwpn, &npiv_wwnn) < 0)
		return ERR_PTR(-EINVAL);

	lport = kzalloc(sizeof(struct tcm_qla2xxx_lport), GFP_KERNEL);
	if (!lport) {
		pr_err("Unable to allocate struct tcm_qla2xxx_lport for NPIV\n");
		return ERR_PTR(-ENOMEM);
	}
	lport->lport_npiv_wwpn = npiv_wwpn;
	lport->lport_npiv_wwnn = npiv_wwnn;
	sprintf(lport->lport_naa_name, "naa.%016llx", (unsigned long long) npiv_wwpn);

	ret = tcm_qla2xxx_init_lport(lport);
	if (ret != 0)
		goto out;

	ret = qlt_lport_register(lport, phys_wwpn, npiv_wwpn, npiv_wwnn,
				 tcm_qla2xxx_lport_register_npiv_cb);
	if (ret != 0)
		goto out_lport;

	return &lport->lport_wwn;
out_lport:
	vfree(lport->lport_loopid_map);
	btree_destroy32(&lport->lport_fcport_map);
out:
	kfree(lport);
	return ERR_PTR(ret);
}