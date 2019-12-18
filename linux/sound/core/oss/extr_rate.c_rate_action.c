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
struct snd_pcm_plugin {int dummy; } ;
typedef  enum snd_pcm_plugin_action { ____Placeholder_snd_pcm_plugin_action } snd_pcm_plugin_action ;

/* Variables and functions */
 int ENXIO ; 
#define  INIT 129 
#define  PREPARE 128 
 int /*<<< orphan*/  rate_init (struct snd_pcm_plugin*) ; 
 scalar_t__ snd_BUG_ON (int) ; 

__attribute__((used)) static int rate_action(struct snd_pcm_plugin *plugin,
		       enum snd_pcm_plugin_action action,
		       unsigned long udata)
{
	if (snd_BUG_ON(!plugin))
		return -ENXIO;
	switch (action) {
	case INIT:
	case PREPARE:
		rate_init(plugin);
		break;
	default:
		break;
	}
	return 0;	/* silenty ignore other actions */
}