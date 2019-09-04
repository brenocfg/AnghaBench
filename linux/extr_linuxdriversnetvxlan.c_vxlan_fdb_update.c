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
typedef  union vxlan_addr {int dummy; } vxlan_addr ;
typedef  int /*<<< orphan*/  u8 ;
struct vxlan_rdst {int dummy; } ;
struct vxlan_fdb {int state; scalar_t__ flags; int /*<<< orphan*/  const* eth_addr; void* updated; } ;
struct vxlan_dev {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ __u8 ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int __u16 ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EEXIST ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 int NLM_F_APPEND ; 
 int NLM_F_CREATE ; 
 int NLM_F_EXCL ; 
 int NLM_F_REPLACE ; 
 int /*<<< orphan*/  RTM_NEWNEIGH ; 
 struct vxlan_fdb* __vxlan_find_mac (struct vxlan_dev*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct vxlan_rdst* first_remote_rtnl (struct vxlan_fdb*) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/  const*) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/  const*) ; 
 void* jiffies ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,...) ; 
 int vxlan_fdb_append (struct vxlan_fdb*,union vxlan_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vxlan_rdst**) ; 
 int vxlan_fdb_create (struct vxlan_dev*,int /*<<< orphan*/  const*,union vxlan_addr*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct vxlan_fdb**) ; 
 int /*<<< orphan*/  vxlan_fdb_notify (struct vxlan_dev*,struct vxlan_fdb*,struct vxlan_rdst*,int /*<<< orphan*/ ) ; 
 int vxlan_fdb_replace (struct vxlan_fdb*,union vxlan_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vxlan_fdb_update(struct vxlan_dev *vxlan,
			    const u8 *mac, union vxlan_addr *ip,
			    __u16 state, __u16 flags,
			    __be16 port, __be32 src_vni, __be32 vni,
			    __u32 ifindex, __u8 ndm_flags)
{
	struct vxlan_rdst *rd = NULL;
	struct vxlan_fdb *f;
	int notify = 0;
	int rc;

	f = __vxlan_find_mac(vxlan, mac, src_vni);
	if (f) {
		if (flags & NLM_F_EXCL) {
			netdev_dbg(vxlan->dev,
				   "lost race to create %pM\n", mac);
			return -EEXIST;
		}
		if (f->state != state) {
			f->state = state;
			f->updated = jiffies;
			notify = 1;
		}
		if (f->flags != ndm_flags) {
			f->flags = ndm_flags;
			f->updated = jiffies;
			notify = 1;
		}
		if ((flags & NLM_F_REPLACE)) {
			/* Only change unicasts */
			if (!(is_multicast_ether_addr(f->eth_addr) ||
			     is_zero_ether_addr(f->eth_addr))) {
				notify |= vxlan_fdb_replace(f, ip, port, vni,
							   ifindex);
			} else
				return -EOPNOTSUPP;
		}
		if ((flags & NLM_F_APPEND) &&
		    (is_multicast_ether_addr(f->eth_addr) ||
		     is_zero_ether_addr(f->eth_addr))) {
			rc = vxlan_fdb_append(f, ip, port, vni, ifindex, &rd);

			if (rc < 0)
				return rc;
			notify |= rc;
		}
	} else {
		if (!(flags & NLM_F_CREATE))
			return -ENOENT;

		/* Disallow replace to add a multicast entry */
		if ((flags & NLM_F_REPLACE) &&
		    (is_multicast_ether_addr(mac) || is_zero_ether_addr(mac)))
			return -EOPNOTSUPP;

		netdev_dbg(vxlan->dev, "add %pM -> %pIS\n", mac, ip);
		rc = vxlan_fdb_create(vxlan, mac, ip, state, port, src_vni,
				      vni, ifindex, ndm_flags, &f);
		if (rc < 0)
			return rc;
		notify = 1;
	}

	if (notify) {
		if (rd == NULL)
			rd = first_remote_rtnl(f);
		vxlan_fdb_notify(vxlan, f, rd, RTM_NEWNEIGH);
	}

	return 0;
}