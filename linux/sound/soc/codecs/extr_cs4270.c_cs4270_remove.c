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
struct cs4270_private {int /*<<< orphan*/  supplies; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cs4270_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void cs4270_remove(struct snd_soc_component *component)
{
	struct cs4270_private *cs4270 = snd_soc_component_get_drvdata(component);

	regulator_bulk_disable(ARRAY_SIZE(cs4270->supplies), cs4270->supplies);
}