#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_bridge_port {scalar_t__ state; } ;
struct net_bridge_fdb_entry {int is_local; int is_static; int added_by_user; void* updated; void* used; struct net_bridge_port* dst; } ;
struct net_bridge {TYPE_1__* dev; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int __u16 ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ BR_STATE_FORWARDING ; 
 scalar_t__ BR_STATE_LEARNING ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EPERM ; 
 int NLM_F_CREATE ; 
 int NLM_F_EXCL ; 
 int NUD_NOARP ; 
 int NUD_PERMANENT ; 
 int /*<<< orphan*/  RTM_NEWNEIGH ; 
 struct net_bridge_fdb_entry* br_fdb_find (struct net_bridge*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  fdb_add_hw_addr (struct net_bridge*,int /*<<< orphan*/  const*) ; 
 struct net_bridge_fdb_entry* fdb_create (struct net_bridge*,struct net_bridge_port*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdb_del_hw_addr (struct net_bridge*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fdb_notify (struct net_bridge*,struct net_bridge_fdb_entry*,int /*<<< orphan*/ ,int) ; 
 int fdb_to_nud (struct net_bridge*,struct net_bridge_fdb_entry*) ; 
 void* jiffies ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fdb_add_entry(struct net_bridge *br, struct net_bridge_port *source,
			 const __u8 *addr, __u16 state, __u16 flags, __u16 vid)
{
	struct net_bridge_fdb_entry *fdb;
	bool modified = false;

	/* If the port cannot learn allow only local and static entries */
	if (source && !(state & NUD_PERMANENT) && !(state & NUD_NOARP) &&
	    !(source->state == BR_STATE_LEARNING ||
	      source->state == BR_STATE_FORWARDING))
		return -EPERM;

	if (!source && !(state & NUD_PERMANENT)) {
		pr_info("bridge: RTM_NEWNEIGH %s without NUD_PERMANENT\n",
			br->dev->name);
		return -EINVAL;
	}

	fdb = br_fdb_find(br, addr, vid);
	if (fdb == NULL) {
		if (!(flags & NLM_F_CREATE))
			return -ENOENT;

		fdb = fdb_create(br, source, addr, vid, 0, 0);
		if (!fdb)
			return -ENOMEM;

		modified = true;
	} else {
		if (flags & NLM_F_EXCL)
			return -EEXIST;

		if (fdb->dst != source) {
			fdb->dst = source;
			modified = true;
		}
	}

	if (fdb_to_nud(br, fdb) != state) {
		if (state & NUD_PERMANENT) {
			fdb->is_local = 1;
			if (!fdb->is_static) {
				fdb->is_static = 1;
				fdb_add_hw_addr(br, addr);
			}
		} else if (state & NUD_NOARP) {
			fdb->is_local = 0;
			if (!fdb->is_static) {
				fdb->is_static = 1;
				fdb_add_hw_addr(br, addr);
			}
		} else {
			fdb->is_local = 0;
			if (fdb->is_static) {
				fdb->is_static = 0;
				fdb_del_hw_addr(br, addr);
			}
		}

		modified = true;
	}
	fdb->added_by_user = 1;

	fdb->used = jiffies;
	if (modified) {
		fdb->updated = jiffies;
		fdb_notify(br, fdb, RTM_NEWNEIGH, true);
	}

	return 0;
}