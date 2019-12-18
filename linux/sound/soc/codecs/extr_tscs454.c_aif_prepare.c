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
struct aif {int /*<<< orphan*/  master; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int aif_set_master (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
int aif_prepare(struct snd_soc_component *component, struct aif *aif)
{
	int ret;

	ret = aif_set_master(component, aif->id, aif->master);
	if (ret < 0)
		return ret;

	return 0;
}