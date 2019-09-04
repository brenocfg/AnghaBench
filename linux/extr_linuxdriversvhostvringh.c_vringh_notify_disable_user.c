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
 int /*<<< orphan*/  __vringh_notify_disable (struct vringh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putu16_user ; 

void vringh_notify_disable_user(struct vringh *vrh)
{
	__vringh_notify_disable(vrh, putu16_user);
}