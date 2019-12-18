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
struct snd_info_buffer {int dummy; } ;

/* Variables and functions */
 int SNDRV_CARDS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 
 char*** snd_sndstat_strings ; 
 int /*<<< orphan*/  strings ; 

__attribute__((used)) static int snd_sndstat_show_strings(struct snd_info_buffer *buf, char *id, int dev)
{
	int idx, ok = -1;
	char *str;

	snd_iprintf(buf, "\n%s:", id);
	mutex_lock(&strings);
	for (idx = 0; idx < SNDRV_CARDS; idx++) {
		str = snd_sndstat_strings[idx][dev];
		if (str) {
			if (ok < 0) {
				snd_iprintf(buf, "\n");
				ok++;
			}
			snd_iprintf(buf, "%i: %s\n", idx, str);
		}
	}
	mutex_unlock(&strings);
	if (ok < 0)
		snd_iprintf(buf, " NOT ENABLED IN CONFIG\n");
	return ok;
}