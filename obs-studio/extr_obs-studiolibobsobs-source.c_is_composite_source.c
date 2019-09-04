#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int output_flags; } ;
struct obs_source {TYPE_1__ info; } ;

/* Variables and functions */
 int OBS_SOURCE_COMPOSITE ; 

__attribute__((used)) static inline bool is_composite_source(const struct obs_source *source)
{
	return source->info.output_flags & OBS_SOURCE_COMPOSITE;
}