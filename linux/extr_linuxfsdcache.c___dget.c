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
struct dentry {int /*<<< orphan*/  d_lockref; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockref_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void __dget(struct dentry *dentry)
{
	lockref_get(&dentry->d_lockref);
}