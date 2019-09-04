#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm {int dummy; } ;
struct snd_line6_pcm {TYPE_1__* line6; int /*<<< orphan*/  in; int /*<<< orphan*/  out; } ;
struct TYPE_2__ {int /*<<< orphan*/  iso_buffers; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_urbs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct snd_line6_pcm*) ; 
 struct snd_line6_pcm* snd_pcm_chip (struct snd_pcm*) ; 

__attribute__((used)) static void line6_cleanup_pcm(struct snd_pcm *pcm)
{
	struct snd_line6_pcm *line6pcm = snd_pcm_chip(pcm);

	cleanup_urbs(&line6pcm->out, line6pcm->line6->iso_buffers);
	cleanup_urbs(&line6pcm->in, line6pcm->line6->iso_buffers);
	kfree(line6pcm);
}