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
struct vringh {int dummy; } ;

/* Variables and functions */
 int __vringh_notify_enable (struct vringh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getu16_user ; 
 int /*<<< orphan*/  putu16_user ; 

bool vringh_notify_enable_user(struct vringh *vrh)
{
	return __vringh_notify_enable(vrh, getu16_user, putu16_user);
}