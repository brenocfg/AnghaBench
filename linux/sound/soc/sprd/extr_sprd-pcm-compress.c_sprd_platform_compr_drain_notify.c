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
struct sprd_compr_stream {int /*<<< orphan*/  info_area; } ;
struct sprd_compr_playinfo {int dummy; } ;
struct snd_compr_stream {struct snd_compr_runtime* runtime; } ;
struct snd_compr_runtime {struct sprd_compr_stream* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_compr_drain_notify (struct snd_compr_stream*) ; 

__attribute__((used)) static void sprd_platform_compr_drain_notify(void *arg)
{
	struct snd_compr_stream *cstream = arg;
	struct snd_compr_runtime *runtime = cstream->runtime;
	struct sprd_compr_stream *stream = runtime->private_data;

	memset(stream->info_area, 0, sizeof(struct sprd_compr_playinfo));

	snd_compr_drain_notify(cstream);
}