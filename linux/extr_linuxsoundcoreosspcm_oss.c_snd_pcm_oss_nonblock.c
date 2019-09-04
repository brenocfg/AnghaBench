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
struct file {int /*<<< orphan*/  f_lock; int /*<<< orphan*/  f_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_pcm_oss_nonblock(struct file * file)
{
	spin_lock(&file->f_lock);
	file->f_flags |= O_NONBLOCK;
	spin_unlock(&file->f_lock);
	return 0;
}