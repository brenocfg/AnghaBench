#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ transitioning_video; scalar_t__ transitioning_audio; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */

__attribute__((used)) static inline bool transition_active(obs_source_t *transition)
{
	return transition->transitioning_audio ||
	       transition->transitioning_video;
}