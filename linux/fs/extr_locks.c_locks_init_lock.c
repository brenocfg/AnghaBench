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
struct file_lock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  locks_init_lock_heads (struct file_lock*) ; 
 int /*<<< orphan*/  memset (struct file_lock*,int /*<<< orphan*/ ,int) ; 

void locks_init_lock(struct file_lock *fl)
{
	memset(fl, 0, sizeof(struct file_lock));
	locks_init_lock_heads(fl);
}