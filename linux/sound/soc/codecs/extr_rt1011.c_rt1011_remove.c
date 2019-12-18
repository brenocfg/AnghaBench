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
struct snd_soc_component {int dummy; } ;
struct rt1011_priv {int /*<<< orphan*/  regmap; int /*<<< orphan*/  cali_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt1011_reset (int /*<<< orphan*/ ) ; 
 struct rt1011_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void rt1011_remove(struct snd_soc_component *component)
{
	struct rt1011_priv *rt1011 = snd_soc_component_get_drvdata(component);

	cancel_work_sync(&rt1011->cali_work);
	rt1011_reset(rt1011->regmap);
}