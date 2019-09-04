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
struct proc_dir_entry {int /*<<< orphan*/  proc_iops; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool is_empty_pde(const struct proc_dir_entry *pde)
{
	return S_ISDIR(pde->mode) && !pde->proc_iops;
}