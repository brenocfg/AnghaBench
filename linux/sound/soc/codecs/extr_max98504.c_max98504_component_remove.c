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
struct max98504_priv {int /*<<< orphan*/  supplies; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX98504_NUM_SUPPLIES ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct max98504_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void max98504_component_remove(struct snd_soc_component *c)
{
	struct max98504_priv *max98504 = snd_soc_component_get_drvdata(c);

	regulator_bulk_disable(MAX98504_NUM_SUPPLIES, max98504->supplies);
}