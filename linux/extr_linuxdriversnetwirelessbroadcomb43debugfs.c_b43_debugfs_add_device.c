#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_49__   TYPE_9__ ;
typedef  struct TYPE_48__   TYPE_8__ ;
typedef  struct TYPE_47__   TYPE_7__ ;
typedef  struct TYPE_46__   TYPE_6__ ;
typedef  struct TYPE_45__   TYPE_5__ ;
typedef  struct TYPE_44__   TYPE_4__ ;
typedef  struct TYPE_43__   TYPE_3__ ;
typedef  struct TYPE_42__   TYPE_2__ ;
typedef  struct TYPE_41__   TYPE_24__ ;
typedef  struct TYPE_40__   TYPE_23__ ;
typedef  struct TYPE_39__   TYPE_22__ ;
typedef  struct TYPE_38__   TYPE_21__ ;
typedef  struct TYPE_37__   TYPE_20__ ;
typedef  struct TYPE_36__   TYPE_1__ ;
typedef  struct TYPE_35__   TYPE_19__ ;
typedef  struct TYPE_34__   TYPE_18__ ;
typedef  struct TYPE_33__   TYPE_17__ ;
typedef  struct TYPE_32__   TYPE_16__ ;
typedef  struct TYPE_31__   TYPE_15__ ;
typedef  struct TYPE_30__   TYPE_14__ ;
typedef  struct TYPE_29__   TYPE_13__ ;
typedef  struct TYPE_28__   TYPE_12__ ;
typedef  struct TYPE_27__   TYPE_11__ ;
typedef  struct TYPE_26__   TYPE_10__ ;

/* Type definitions */
struct dentry {int dummy; } ;
struct b43_wldev {struct b43_dfsentry* dfsentry; TYPE_24__* wl; } ;
struct b43_txstatus_log {int end; struct b43_dfsentry* log; } ;
struct b43_txstatus {int dummy; } ;
struct TYPE_45__ {struct dentry* dentry; } ;
struct TYPE_44__ {struct dentry* dentry; } ;
struct TYPE_43__ {struct dentry* dentry; } ;
struct TYPE_42__ {struct dentry* dentry; } ;
struct TYPE_36__ {struct dentry* dentry; } ;
struct TYPE_28__ {struct dentry* dentry; } ;
struct TYPE_27__ {struct dentry* dentry; } ;
struct TYPE_26__ {struct dentry* dentry; } ;
struct TYPE_49__ {struct dentry* dentry; } ;
struct TYPE_48__ {struct dentry* dentry; } ;
struct TYPE_47__ {struct dentry* dentry; } ;
struct b43_dfsentry {scalar_t__ subdir; int mmio16read_next; int mmio32read_next; int shm16read_routing_next; int shm16read_addr_next; int shm32read_routing_next; int shm32read_addr_next; TYPE_5__ file_loctls; TYPE_4__ file_restart; TYPE_3__ file_txstat; TYPE_2__ file_mmio32write; TYPE_1__ file_mmio32read; TYPE_12__ file_mmio16write; TYPE_11__ file_mmio16read; TYPE_10__ file_shm32write; TYPE_9__ file_shm32read; TYPE_8__ file_shm16write; TYPE_7__ file_shm16read; struct b43_txstatus_log txstatlog; struct b43_wldev* dev; } ;
typedef  int /*<<< orphan*/  devdir ;
struct TYPE_46__ {int /*<<< orphan*/  wiphy; } ;
struct TYPE_41__ {TYPE_6__* hw; } ;
struct TYPE_40__ {int /*<<< orphan*/  fops; } ;
struct TYPE_39__ {int /*<<< orphan*/  fops; } ;
struct TYPE_38__ {int /*<<< orphan*/  fops; } ;
struct TYPE_37__ {int /*<<< orphan*/  fops; } ;
struct TYPE_35__ {int /*<<< orphan*/  fops; } ;
struct TYPE_34__ {int /*<<< orphan*/  fops; } ;
struct TYPE_33__ {int /*<<< orphan*/  fops; } ;
struct TYPE_32__ {int /*<<< orphan*/  fops; } ;
struct TYPE_31__ {int /*<<< orphan*/  fops; } ;
struct TYPE_30__ {int /*<<< orphan*/  fops; } ;
struct TYPE_29__ {int /*<<< orphan*/  fops; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_NR_LOGGED_TXSTATUS ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  ENODEV ; 
 scalar_t__ ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  __stringify (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_add_dynamic_debug (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43dbg (TYPE_24__*,char*) ; 
 int /*<<< orphan*/  b43err (TYPE_24__*,char*,...) ; 
 struct dentry* debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 struct dentry* debugfs_create_file (int /*<<< orphan*/ ,int,scalar_t__,struct b43_wldev*,int /*<<< orphan*/ *) ; 
 TYPE_23__ fops_loctls ; 
 TYPE_22__ fops_mmio16read ; 
 TYPE_21__ fops_mmio16write ; 
 TYPE_20__ fops_mmio32read ; 
 TYPE_19__ fops_mmio32write ; 
 TYPE_18__ fops_restart ; 
 TYPE_17__ fops_shm16read ; 
 TYPE_16__ fops_shm16write ; 
 TYPE_15__ fops_shm32read ; 
 TYPE_14__ fops_shm32write ; 
 TYPE_13__ fops_txstat ; 
 struct b43_dfsentry* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct b43_dfsentry*) ; 
 struct b43_dfsentry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loctls ; 
 int /*<<< orphan*/  mmio16read ; 
 int /*<<< orphan*/  mmio16write ; 
 int /*<<< orphan*/  mmio32read ; 
 int /*<<< orphan*/  mmio32write ; 
 int /*<<< orphan*/  restart ; 
 int /*<<< orphan*/  rootdir ; 
 int /*<<< orphan*/  shm16read ; 
 int /*<<< orphan*/  shm16write ; 
 int /*<<< orphan*/  shm32read ; 
 int /*<<< orphan*/  shm32write ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  txstat ; 
 char* wiphy_name (int /*<<< orphan*/ ) ; 

void b43_debugfs_add_device(struct b43_wldev *dev)
{
	struct b43_dfsentry *e;
	struct b43_txstatus_log *log;
	char devdir[16];

	B43_WARN_ON(!dev);
	e = kzalloc(sizeof(*e), GFP_KERNEL);
	if (!e) {
		b43err(dev->wl, "debugfs: add device OOM\n");
		return;
	}
	e->dev = dev;
	log = &e->txstatlog;
	log->log = kcalloc(B43_NR_LOGGED_TXSTATUS,
			   sizeof(struct b43_txstatus), GFP_KERNEL);
	if (!log->log) {
		b43err(dev->wl, "debugfs: add device txstatus OOM\n");
		kfree(e);
		return;
	}
	log->end = -1;

	dev->dfsentry = e;

	snprintf(devdir, sizeof(devdir), "%s", wiphy_name(dev->wl->hw->wiphy));
	e->subdir = debugfs_create_dir(devdir, rootdir);
	if (!e->subdir || IS_ERR(e->subdir)) {
		if (e->subdir == ERR_PTR(-ENODEV)) {
			b43dbg(dev->wl, "DebugFS (CONFIG_DEBUG_FS) not "
			       "enabled in kernel config\n");
		} else {
			b43err(dev->wl, "debugfs: cannot create %s directory\n",
			       devdir);
		}
		dev->dfsentry = NULL;
		kfree(log->log);
		kfree(e);
		return;
	}

	e->mmio16read_next = 0xFFFF; /* invalid address */
	e->mmio32read_next = 0xFFFF; /* invalid address */
	e->shm16read_routing_next = 0xFFFFFFFF; /* invalid routing */
	e->shm16read_addr_next = 0xFFFFFFFF; /* invalid address */
	e->shm32read_routing_next = 0xFFFFFFFF; /* invalid routing */
	e->shm32read_addr_next = 0xFFFFFFFF; /* invalid address */

#define ADD_FILE(name, mode)	\
	do {							\
		struct dentry *d;				\
		d = debugfs_create_file(__stringify(name),	\
					mode, e->subdir, dev,	\
					&fops_##name.fops);	\
		e->file_##name.dentry = NULL;			\
		if (!IS_ERR(d))					\
			e->file_##name.dentry = d;		\
	} while (0)


	ADD_FILE(shm16read, 0600);
	ADD_FILE(shm16write, 0200);
	ADD_FILE(shm32read, 0600);
	ADD_FILE(shm32write, 0200);
	ADD_FILE(mmio16read, 0600);
	ADD_FILE(mmio16write, 0200);
	ADD_FILE(mmio32read, 0600);
	ADD_FILE(mmio32write, 0200);
	ADD_FILE(txstat, 0400);
	ADD_FILE(restart, 0200);
	ADD_FILE(loctls, 0400);

#undef ADD_FILE

	b43_add_dynamic_debug(dev);
}