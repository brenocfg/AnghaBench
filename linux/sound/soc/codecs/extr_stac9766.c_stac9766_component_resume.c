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
struct snd_ac97 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAC9766_VENDOR_ID ; 
 int /*<<< orphan*/  STAC9766_VENDOR_ID_MASK ; 
 int snd_ac97_reset (struct snd_ac97*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_ac97* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int stac9766_component_resume(struct snd_soc_component *component)
{
	struct snd_ac97 *ac97 = snd_soc_component_get_drvdata(component);

	return snd_ac97_reset(ac97, true, STAC9766_VENDOR_ID,
		STAC9766_VENDOR_ID_MASK);
}