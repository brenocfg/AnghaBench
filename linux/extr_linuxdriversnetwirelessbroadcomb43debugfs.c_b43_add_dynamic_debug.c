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
struct dentry {int dummy; } ;
struct b43_wldev {struct b43_dfsentry* dfsentry; } ;
struct b43_dfsentry {int* dyn_debug; struct dentry** dyn_debug_dentries; int /*<<< orphan*/  subdir; } ;

/* Variables and functions */
 size_t B43_DBG_DMAOVERFLOW ; 
 size_t B43_DBG_DMAVERBOSE ; 
 size_t B43_DBG_FIRMWARE ; 
 size_t B43_DBG_KEYS ; 
 size_t B43_DBG_LO ; 
 size_t B43_DBG_PWORK_FAST ; 
 size_t B43_DBG_PWORK_STOP ; 
 size_t B43_DBG_VERBOSESTATS ; 
 size_t B43_DBG_XMITPOWER ; 
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 struct dentry* debugfs_create_bool (char*,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void b43_add_dynamic_debug(struct b43_wldev *dev)
{
	struct b43_dfsentry *e = dev->dfsentry;
	struct dentry *d;

#define add_dyn_dbg(name, id, initstate) do {		\
	e->dyn_debug[id] = (initstate);			\
	d = debugfs_create_bool(name, 0600, e->subdir,	\
				&(e->dyn_debug[id]));	\
	if (!IS_ERR(d))					\
		e->dyn_debug_dentries[id] = d;		\
				} while (0)

	add_dyn_dbg("debug_xmitpower", B43_DBG_XMITPOWER, false);
	add_dyn_dbg("debug_dmaoverflow", B43_DBG_DMAOVERFLOW, false);
	add_dyn_dbg("debug_dmaverbose", B43_DBG_DMAVERBOSE, false);
	add_dyn_dbg("debug_pwork_fast", B43_DBG_PWORK_FAST, false);
	add_dyn_dbg("debug_pwork_stop", B43_DBG_PWORK_STOP, false);
	add_dyn_dbg("debug_lo", B43_DBG_LO, false);
	add_dyn_dbg("debug_firmware", B43_DBG_FIRMWARE, false);
	add_dyn_dbg("debug_keys", B43_DBG_KEYS, false);
	add_dyn_dbg("debug_verbose_stats", B43_DBG_VERBOSESTATS, false);

#undef add_dyn_dbg
}