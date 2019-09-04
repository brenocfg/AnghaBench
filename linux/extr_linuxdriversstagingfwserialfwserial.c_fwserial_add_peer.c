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
typedef  int u64 ;
struct virt_plug_params {int dummy; } ;
struct fwtty_port {int dummy; } ;
struct fwtty_peer {int guid; int generation; unsigned long long mgmt_addr; int /*<<< orphan*/  connect; int /*<<< orphan*/  lock; struct fwtty_port* port; struct fw_unit* unit; int /*<<< orphan*/  list; struct fw_serial* serial; int /*<<< orphan*/  work; int /*<<< orphan*/  timer; int /*<<< orphan*/  node_id; int /*<<< orphan*/  speed; int /*<<< orphan*/  max_payload; } ;
struct device {int dummy; } ;
struct fw_unit {int /*<<< orphan*/  directory; struct device device; } ;
struct fw_serial {struct fwtty_peer* self; int /*<<< orphan*/  peer_list; } ;
struct fw_device {int* config_rom; int generation; scalar_t__ is_local; int /*<<< orphan*/  node_id; int /*<<< orphan*/  max_speed; } ;
struct fw_csr_iterator {int dummy; } ;

/* Variables and functions */
 int CSR_DEPENDENT_INFO ; 
 int CSR_OFFSET ; 
 unsigned long long CSR_REGISTER_BASE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FWPS_NOT_ATTACHED ; 
 int /*<<< orphan*/  FWPS_NO_MGMT_ADDR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct fwtty_port*) ; 
 scalar_t__ auto_connect ; 
 scalar_t__ create_loop_dev ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct fwtty_peer*) ; 
 int /*<<< orphan*/  device_max_receive (struct fw_device*) ; 
 int /*<<< orphan*/  fill_plug_params (struct virt_plug_params*,struct fwtty_port*) ; 
 int /*<<< orphan*/  fw_csr_iterator_init (struct fw_csr_iterator*,int /*<<< orphan*/ ) ; 
 scalar_t__ fw_csr_iterator_next (struct fw_csr_iterator*,int*,int*) ; 
 struct fw_device* fw_parent_device (struct fw_unit*) ; 
 int /*<<< orphan*/  fwserial_auto_connect ; 
 struct fwtty_port* fwserial_claim_port (struct fwtty_peer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwserial_peer_workfn ; 
 int /*<<< orphan*/  fwserial_plug_timeout ; 
 int /*<<< orphan*/  fwserial_virt_plug_complete (struct fwtty_peer*,struct virt_plug_params*) ; 
 int /*<<< orphan*/  fwtty_info (struct fw_unit**,char*,unsigned long long) ; 
 int /*<<< orphan*/  fwtty_write_port_status (struct fwtty_port*) ; 
 struct fwtty_peer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_speed_to_max_payload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_ttys ; 
 int /*<<< orphan*/  peer_set_state (struct fwtty_peer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fwserial_add_peer(struct fw_serial *serial, struct fw_unit *unit)
{
	struct device *dev = &unit->device;
	struct fw_device  *parent = fw_parent_device(unit);
	struct fwtty_peer *peer;
	struct fw_csr_iterator ci;
	int key, val;
	int generation;

	peer = kzalloc(sizeof(*peer), GFP_KERNEL);
	if (!peer)
		return -ENOMEM;

	peer_set_state(peer, FWPS_NOT_ATTACHED);

	dev_set_drvdata(dev, peer);
	peer->unit = unit;
	peer->guid = (u64)parent->config_rom[3] << 32 | parent->config_rom[4];
	peer->speed = parent->max_speed;
	peer->max_payload = min(device_max_receive(parent),
				link_speed_to_max_payload(peer->speed));

	generation = parent->generation;
	smp_rmb();
	peer->node_id = parent->node_id;
	smp_wmb();
	peer->generation = generation;

	/* retrieve the mgmt bus addr from the unit directory */
	fw_csr_iterator_init(&ci, unit->directory);
	while (fw_csr_iterator_next(&ci, &key, &val)) {
		if (key == (CSR_OFFSET | CSR_DEPENDENT_INFO)) {
			peer->mgmt_addr = CSR_REGISTER_BASE + 4 * val;
			break;
		}
	}
	if (peer->mgmt_addr == 0ULL) {
		/*
		 * No mgmt address effectively disables VIRT_CABLE_PLUG -
		 * this peer will not be able to attach to a remote
		 */
		peer_set_state(peer, FWPS_NO_MGMT_ADDR);
	}

	spin_lock_init(&peer->lock);
	peer->port = NULL;

	timer_setup(&peer->timer, fwserial_plug_timeout, 0);
	INIT_WORK(&peer->work, fwserial_peer_workfn);
	INIT_DELAYED_WORK(&peer->connect, fwserial_auto_connect);

	/* associate peer with specific fw_card */
	peer->serial = serial;
	list_add_rcu(&peer->list, &serial->peer_list);

	fwtty_info(&peer->unit, "peer added (guid:%016llx)\n",
		   (unsigned long long)peer->guid);

	/* identify the local unit & virt cable to loopback port */
	if (parent->is_local) {
		serial->self = peer;
		if (create_loop_dev) {
			struct fwtty_port *port;

			port = fwserial_claim_port(peer, num_ttys);
			if (!IS_ERR(port)) {
				struct virt_plug_params params;

				spin_lock_bh(&peer->lock);
				peer->port = port;
				fill_plug_params(&params, port);
				fwserial_virt_plug_complete(peer, &params);
				spin_unlock_bh(&peer->lock);

				fwtty_write_port_status(port);
			}
		}

	} else if (auto_connect) {
		/* auto-attach to remote units only (if policy allows) */
		schedule_delayed_work(&peer->connect, 1);
	}

	return 0;
}