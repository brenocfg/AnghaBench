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

/* Variables and functions */
 int /*<<< orphan*/  __put_mountpoint (struct mountpoint*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ex_mountpoints ; 

__attribute__((used)) static void put_mountpoint(struct mountpoint *mp)
{
	__put_mountpoint(mp, &ex_mountpoints);
}