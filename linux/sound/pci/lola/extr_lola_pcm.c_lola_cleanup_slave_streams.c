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
struct lola_stream {int index; scalar_t__ opened; struct lola_stream* master; } ;
struct lola_pcm {int num_streams; struct lola_stream* streams; } ;

/* Variables and functions */

__attribute__((used)) static void lola_cleanup_slave_streams(struct lola_pcm *pcm,
				       struct lola_stream *str)
{
	int i;
	for (i = str->index + 1; i < pcm->num_streams; i++) {
		struct lola_stream *s = &pcm->streams[i];
		if (s->master != str)
			break;
		s->master = NULL;
		s->opened = 0;
	}
}