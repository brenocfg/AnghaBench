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
struct ssm2602_priv {int /*<<< orphan*/  regmap; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 struct ssm2602_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int ssm2602_resume(struct snd_soc_component *component)
{
	struct ssm2602_priv *ssm2602 = snd_soc_component_get_drvdata(component);

	regcache_sync(ssm2602->regmap);

	return 0;
}