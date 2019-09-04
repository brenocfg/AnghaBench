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
struct wil6210_priv {int dummy; } ;
struct dentry {int dummy; } ;
struct dbg_off {int type; scalar_t__ name; int /*<<< orphan*/  off; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR_OR_NULL (struct dentry*) ; 
 int /*<<< orphan*/  PTR_ERR (struct dentry*) ; 
 struct dentry* debugfs_create_u32 (scalar_t__,int /*<<< orphan*/ ,struct dentry*,void*) ; 
 struct dentry* debugfs_create_u8 (scalar_t__,int /*<<< orphan*/ ,struct dentry*,void*) ; 
 struct dentry* debugfs_create_x32 (scalar_t__,int /*<<< orphan*/ ,struct dentry*,void*) ; 
#define  doff_io32 132 
#define  doff_u32 131 
#define  doff_u8 130 
#define  doff_ulong 129 
#define  doff_x32 128 
 struct dentry* wil_debugfs_create_iomem_x32 (scalar_t__,int /*<<< orphan*/ ,struct dentry*,void*,struct wil6210_priv*) ; 
 struct dentry* wil_debugfs_create_ulong (scalar_t__,int /*<<< orphan*/ ,struct dentry*,void*) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wil6210_debugfs_init_offset(struct wil6210_priv *wil,
					struct dentry *dbg, void *base,
					const struct dbg_off * const tbl)
{
	int i;

	for (i = 0; tbl[i].name; i++) {
		struct dentry *f;

		switch (tbl[i].type) {
		case doff_u32:
			f = debugfs_create_u32(tbl[i].name, tbl[i].mode, dbg,
					       base + tbl[i].off);
			break;
		case doff_x32:
			f = debugfs_create_x32(tbl[i].name, tbl[i].mode, dbg,
					       base + tbl[i].off);
			break;
		case doff_ulong:
			f = wil_debugfs_create_ulong(tbl[i].name, tbl[i].mode,
						     dbg, base + tbl[i].off);
			break;
		case doff_io32:
			f = wil_debugfs_create_iomem_x32(tbl[i].name,
							 tbl[i].mode, dbg,
							 base + tbl[i].off,
							 wil);
			break;
		case doff_u8:
			f = debugfs_create_u8(tbl[i].name, tbl[i].mode, dbg,
					      base + tbl[i].off);
			break;
		default:
			f = ERR_PTR(-EINVAL);
		}
		if (IS_ERR_OR_NULL(f))
			wil_err(wil, "Create file \"%s\": err %ld\n",
				tbl[i].name, PTR_ERR(f));
	}
}