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
struct trace_array {scalar_t__ dir; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DEBUG_FS ; 
 int /*<<< orphan*/  ENODEV ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ debugfs_create_automount (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_initialized () ; 
 struct trace_array global_trace ; 
 int /*<<< orphan*/  trace_automount ; 
 int /*<<< orphan*/  tracefs_initialized () ; 

struct dentry *tracing_init_dentry(void)
{
	struct trace_array *tr = &global_trace;

	/* The top level trace array uses  NULL as parent */
	if (tr->dir)
		return NULL;

	if (WARN_ON(!tracefs_initialized()) ||
		(IS_ENABLED(CONFIG_DEBUG_FS) &&
		 WARN_ON(!debugfs_initialized())))
		return ERR_PTR(-ENODEV);

	/*
	 * As there may still be users that expect the tracing
	 * files to exist in debugfs/tracing, we must automount
	 * the tracefs file system there, so older tools still
	 * work with the newer kerenl.
	 */
	tr->dir = debugfs_create_automount("tracing", NULL,
					   trace_automount, NULL);

	return NULL;
}