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
struct nvme_fc_port_info {int /*<<< orphan*/  port_id; int /*<<< orphan*/  port_role; int /*<<< orphan*/  port_name; int /*<<< orphan*/  node_name; } ;
struct nvme_fc_local_port {struct fcloop_lport_priv* private; } ;
struct fcloop_lport_priv {struct fcloop_lport* lport; } ;
struct fcloop_lport {int mask; int /*<<< orphan*/  lport_list; struct nvme_fc_local_port* localport; int /*<<< orphan*/  fcaddr; int /*<<< orphan*/  roles; int /*<<< orphan*/  wwpn; int /*<<< orphan*/  wwnn; } ;
struct fcloop_ctrl_options {int mask; int /*<<< orphan*/  lport_list; struct nvme_fc_local_port* localport; int /*<<< orphan*/  fcaddr; int /*<<< orphan*/  roles; int /*<<< orphan*/  wwpn; int /*<<< orphan*/  wwnn; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  pinfo ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int LPORT_OPTS ; 
 int /*<<< orphan*/  fcloop_lock ; 
 int /*<<< orphan*/  fcloop_lports ; 
 int fcloop_parse_options (struct fcloop_lport*,char const*) ; 
 int /*<<< orphan*/  fctemplate ; 
 int /*<<< orphan*/  kfree (struct fcloop_lport*) ; 
 struct fcloop_lport* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct nvme_fc_port_info*,int /*<<< orphan*/ ,int) ; 
 int nvme_fc_register_localport (struct nvme_fc_port_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nvme_fc_local_port**) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static ssize_t
fcloop_create_local_port(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct nvme_fc_port_info pinfo;
	struct fcloop_ctrl_options *opts;
	struct nvme_fc_local_port *localport;
	struct fcloop_lport *lport;
	struct fcloop_lport_priv *lport_priv;
	unsigned long flags;
	int ret = -ENOMEM;

	lport = kzalloc(sizeof(*lport), GFP_KERNEL);
	if (!lport)
		return -ENOMEM;

	opts = kzalloc(sizeof(*opts), GFP_KERNEL);
	if (!opts)
		goto out_free_lport;

	ret = fcloop_parse_options(opts, buf);
	if (ret)
		goto out_free_opts;

	/* everything there ? */
	if ((opts->mask & LPORT_OPTS) != LPORT_OPTS) {
		ret = -EINVAL;
		goto out_free_opts;
	}

	memset(&pinfo, 0, sizeof(pinfo));
	pinfo.node_name = opts->wwnn;
	pinfo.port_name = opts->wwpn;
	pinfo.port_role = opts->roles;
	pinfo.port_id = opts->fcaddr;

	ret = nvme_fc_register_localport(&pinfo, &fctemplate, NULL, &localport);
	if (!ret) {
		/* success */
		lport_priv = localport->private;
		lport_priv->lport = lport;

		lport->localport = localport;
		INIT_LIST_HEAD(&lport->lport_list);

		spin_lock_irqsave(&fcloop_lock, flags);
		list_add_tail(&lport->lport_list, &fcloop_lports);
		spin_unlock_irqrestore(&fcloop_lock, flags);
	}

out_free_opts:
	kfree(opts);
out_free_lport:
	/* free only if we're going to fail */
	if (ret)
		kfree(lport);

	return ret ? ret : count;
}