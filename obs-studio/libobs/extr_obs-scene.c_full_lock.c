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
struct obs_scene {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  audio_lock (struct obs_scene*) ; 
 int /*<<< orphan*/  video_lock (struct obs_scene*) ; 

__attribute__((used)) static inline void full_lock(struct obs_scene *scene)
{
	video_lock(scene);
	audio_lock(scene);
}