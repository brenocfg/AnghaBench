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
struct snd_soc_dapm_widget {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct snd_soc_dapm_widget* kmemdup (struct snd_soc_dapm_widget const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct snd_soc_dapm_widget *dapm_cnew_widget(
	const struct snd_soc_dapm_widget *_widget)
{
	return kmemdup(_widget, sizeof(*_widget), GFP_KERNEL);
}