#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_timer_user {int /*<<< orphan*/  ticks; TYPE_1__* timeri; scalar_t__ last_resolution; } ;
struct file {struct snd_timer_user* private_data; } ;
struct TYPE_3__ {scalar_t__ lost; } ;

/* Variables and functions */
 int EBADFD ; 
 int snd_timer_start (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_timer_stop (TYPE_1__*) ; 

__attribute__((used)) static int snd_timer_user_start(struct file *file)
{
	int err;
	struct snd_timer_user *tu;

	tu = file->private_data;
	if (!tu->timeri)
		return -EBADFD;
	snd_timer_stop(tu->timeri);
	tu->timeri->lost = 0;
	tu->last_resolution = 0;
	err = snd_timer_start(tu->timeri, tu->ticks);
	if (err < 0)
		return err;
	return 0;
}