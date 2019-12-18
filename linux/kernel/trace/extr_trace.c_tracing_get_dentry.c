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
struct trace_array {int flags; struct dentry* dir; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int TRACE_ARRAY_FL_GLOBAL ; 
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static struct dentry *tracing_get_dentry(struct trace_array *tr)
{
	if (WARN_ON(!tr->dir))
		return ERR_PTR(-ENODEV);

	/* Top directory uses NULL as the parent */
	if (tr->flags & TRACE_ARRAY_FL_GLOBAL)
		return NULL;

	/* All sub buffers have a descriptor */
	return tr->dir;
}