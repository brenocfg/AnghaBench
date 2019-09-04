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
struct snd_pcm_substream {int dummy; } ;
struct onyx {int /*<<< orphan*/  mutex; int /*<<< orphan*/  open_count; } ;
struct codec_info_item {struct onyx* codec_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int onyx_open(struct codec_info_item *cii,
		     struct snd_pcm_substream *substream)
{
	struct onyx *onyx = cii->codec_data;

	mutex_lock(&onyx->mutex);
	onyx->open_count++;
	mutex_unlock(&onyx->mutex);

	return 0;
}