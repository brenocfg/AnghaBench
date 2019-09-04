#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  owner; } ;
struct TYPE_6__ {TYPE_1__ mach; } ;
struct TYPE_5__ {scalar_t__ busy; } ;

/* Variables and functions */
 TYPE_3__ dmasound ; 
 int /*<<< orphan*/  dmasound_core_mutex ; 
 TYPE_2__ mixer ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mixer_release(struct inode *inode, struct file *file)
{
	mutex_lock(&dmasound_core_mutex);
	mixer.busy = 0;
	module_put(dmasound.mach.owner);
	mutex_unlock(&dmasound_core_mutex);
	return 0;
}