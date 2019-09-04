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
struct mountpoint {int dummy; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __attach_mnt (struct mount*,struct mount*) ; 
 int /*<<< orphan*/  mnt_set_mountpoint (struct mount*,struct mountpoint*,struct mount*) ; 

__attribute__((used)) static void attach_mnt(struct mount *mnt,
			struct mount *parent,
			struct mountpoint *mp)
{
	mnt_set_mountpoint(parent, mp, mnt);
	__attach_mnt(mnt, parent);
}