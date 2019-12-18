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
 int /*<<< orphan*/  generic_acomp_notifier_set (struct drm_audio_component*,int) ; 

__attribute__((used)) static void generic_acomp_master_unbind(struct device *dev,
					struct drm_audio_component *acomp)
{
	generic_acomp_notifier_set(acomp, false);
}