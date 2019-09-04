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
struct snd_rawmidi_runtime {int /*<<< orphan*/  sleep; } ;
struct snd_rawmidi_file {TYPE_1__* output; TYPE_1__* input; } ;
struct file {struct snd_rawmidi_file* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_3__ {struct snd_rawmidi_runtime* runtime; } ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_rawmidi_input_trigger (TYPE_1__*,int) ; 
 scalar_t__ snd_rawmidi_ready (TYPE_1__*) ; 

__attribute__((used)) static __poll_t snd_rawmidi_poll(struct file *file, poll_table *wait)
{
	struct snd_rawmidi_file *rfile;
	struct snd_rawmidi_runtime *runtime;
	__poll_t mask;

	rfile = file->private_data;
	if (rfile->input != NULL) {
		runtime = rfile->input->runtime;
		snd_rawmidi_input_trigger(rfile->input, 1);
		poll_wait(file, &runtime->sleep, wait);
	}
	if (rfile->output != NULL) {
		runtime = rfile->output->runtime;
		poll_wait(file, &runtime->sleep, wait);
	}
	mask = 0;
	if (rfile->input != NULL) {
		if (snd_rawmidi_ready(rfile->input))
			mask |= EPOLLIN | EPOLLRDNORM;
	}
	if (rfile->output != NULL) {
		if (snd_rawmidi_ready(rfile->output))
			mask |= EPOLLOUT | EPOLLWRNORM;
	}
	return mask;
}