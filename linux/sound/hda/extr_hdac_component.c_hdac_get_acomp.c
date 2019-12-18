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
struct drm_audio_component {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct drm_audio_component* devres_find (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdac_acomp_release ; 

__attribute__((used)) static struct drm_audio_component *hdac_get_acomp(struct device *dev)
{
	return devres_find(dev, hdac_acomp_release, NULL, NULL);
}