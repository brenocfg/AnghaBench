#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct dentry {int dummy; } ;
struct b43legacy_wldev {struct b43legacy_dfsentry* dfsentry; TYPE_12__* wl; } ;
struct b43legacy_txstatus_log {int end; struct b43legacy_dfsentry* log; int /*<<< orphan*/  lock; } ;
struct b43legacy_txstatus {int dummy; } ;
struct TYPE_22__ {struct dentry* dentry; } ;
struct TYPE_21__ {struct dentry* dentry; } ;
struct TYPE_20__ {struct dentry* dentry; } ;
struct TYPE_19__ {struct dentry* dentry; } ;
struct TYPE_18__ {struct dentry* dentry; } ;
struct b43legacy_dfsentry {scalar_t__ subdir; TYPE_6__ file_restart; TYPE_5__ file_txstat; TYPE_4__ file_shm; TYPE_3__ file_ucode_regs; TYPE_2__ file_tsf; struct b43legacy_txstatus_log txstatlog; struct b43legacy_wldev* dev; } ;
typedef  int /*<<< orphan*/  devdir ;
struct TYPE_25__ {int /*<<< orphan*/  fops; } ;
struct TYPE_24__ {int /*<<< orphan*/  fops; } ;
struct TYPE_23__ {int /*<<< orphan*/  fops; } ;
struct TYPE_17__ {int /*<<< orphan*/  wiphy; } ;
struct TYPE_16__ {TYPE_1__* hw; } ;
struct TYPE_15__ {int /*<<< orphan*/  fops; } ;
struct TYPE_14__ {int /*<<< orphan*/  fops; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_NR_LOGGED_TXSTATUS ; 
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int /*<<< orphan*/  ENODEV ; 
 scalar_t__ ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  __stringify (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_add_dynamic_debug (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacydbg (TYPE_12__*,char*) ; 
 int /*<<< orphan*/  b43legacyerr (TYPE_12__*,char*,...) ; 
 struct dentry* debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 struct dentry* debugfs_create_file (int /*<<< orphan*/ ,int,scalar_t__,struct b43legacy_wldev*,int /*<<< orphan*/ *) ; 
 TYPE_11__ fops_restart ; 
 TYPE_10__ fops_shm ; 
 TYPE_9__ fops_tsf ; 
 TYPE_8__ fops_txstat ; 
 TYPE_7__ fops_ucode_regs ; 
 struct b43legacy_dfsentry* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct b43legacy_dfsentry*) ; 
 struct b43legacy_dfsentry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restart ; 
 int /*<<< orphan*/  rootdir ; 
 int /*<<< orphan*/  shm ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsf ; 
 int /*<<< orphan*/  txstat ; 
 int /*<<< orphan*/  ucode_regs ; 
 char* wiphy_name (int /*<<< orphan*/ ) ; 

void b43legacy_debugfs_add_device(struct b43legacy_wldev *dev)
{
	struct b43legacy_dfsentry *e;
	struct b43legacy_txstatus_log *log;
	char devdir[16];

	B43legacy_WARN_ON(!dev);
	e = kzalloc(sizeof(*e), GFP_KERNEL);
	if (!e) {
		b43legacyerr(dev->wl, "debugfs: add device OOM\n");
		return;
	}
	e->dev = dev;
	log = &e->txstatlog;
	log->log = kcalloc(B43legacy_NR_LOGGED_TXSTATUS,
			   sizeof(struct b43legacy_txstatus), GFP_KERNEL);
	if (!log->log) {
		b43legacyerr(dev->wl, "debugfs: add device txstatus OOM\n");
		kfree(e);
		return;
	}
	log->end = -1;
	spin_lock_init(&log->lock);

	dev->dfsentry = e;

	snprintf(devdir, sizeof(devdir), "%s", wiphy_name(dev->wl->hw->wiphy));
	e->subdir = debugfs_create_dir(devdir, rootdir);
	if (!e->subdir || IS_ERR(e->subdir)) {
		if (e->subdir == ERR_PTR(-ENODEV)) {
			b43legacydbg(dev->wl, "DebugFS (CONFIG_DEBUG_FS) not "
			       "enabled in kernel config\n");
		} else {
			b43legacyerr(dev->wl, "debugfs: cannot create %s directory\n",
			       devdir);
		}
		dev->dfsentry = NULL;
		kfree(log->log);
		kfree(e);
		return;
	}

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


	ADD_FILE(tsf, 0600);
	ADD_FILE(ucode_regs, 0400);
	ADD_FILE(shm, 0400);
	ADD_FILE(txstat, 0400);
	ADD_FILE(restart, 0200);

#undef ADD_FILE

	b43legacy_add_dynamic_debug(dev);
}