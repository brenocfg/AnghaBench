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
struct file {int f_mode; int /*<<< orphan*/  f_pos_lock; } ;

/* Variables and functions */
 unsigned long FDPUT_POS_UNLOCK ; 
 int FMODE_ATOMIC_POS ; 
 unsigned long __fdget (unsigned int) ; 
 int file_count (struct file*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

unsigned long __fdget_pos(unsigned int fd)
{
	unsigned long v = __fdget(fd);
	struct file *file = (struct file *)(v & ~3);

	if (file && (file->f_mode & FMODE_ATOMIC_POS)) {
		if (file_count(file) > 1) {
			v |= FDPUT_POS_UNLOCK;
			mutex_lock(&file->f_pos_lock);
		}
	}
	return v;
}