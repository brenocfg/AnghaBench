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
struct voicehat_priv {int /*<<< orphan*/  enable_sdmode_work; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct voicehat_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void voicehat_component_remove(struct snd_soc_component *component)
{
	struct voicehat_priv *voicehat =
				snd_soc_component_get_drvdata(component);

	cancel_delayed_work_sync(&voicehat->enable_sdmode_work);
}