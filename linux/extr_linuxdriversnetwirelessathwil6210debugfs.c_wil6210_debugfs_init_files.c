#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wil6210_priv {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  fops; int /*<<< orphan*/  mode; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* dbg_files ; 
 int /*<<< orphan*/  debugfs_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dentry*,struct wil6210_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wil6210_debugfs_init_files(struct wil6210_priv *wil,
				       struct dentry *dbg)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(dbg_files); i++)
		debugfs_create_file(dbg_files[i].name, dbg_files[i].mode, dbg,
				    wil, dbg_files[i].fops);
}