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
struct inode {int dummy; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_opened ; 
 scalar_t__ buffer_pos ; 
 int /*<<< orphan*/  buffer_ready ; 
 int /*<<< orphan*/  dcookie_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oprofile_shutdown () ; 
 int /*<<< orphan*/  oprofile_stop () ; 

__attribute__((used)) static int event_buffer_release(struct inode *inode, struct file *file)
{
	oprofile_stop();
	oprofile_shutdown();
	dcookie_unregister(file->private_data);
	buffer_pos = 0;
	atomic_set(&buffer_ready, 0);
	__clear_bit_unlock(0, &buffer_opened);
	return 0;
}