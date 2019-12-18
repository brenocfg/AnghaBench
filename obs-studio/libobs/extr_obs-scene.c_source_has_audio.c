#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int output_flags; } ;
struct TYPE_5__ {TYPE_1__ info; } ;
typedef  TYPE_2__ obs_source_t ;

/* Variables and functions */
 int OBS_SOURCE_AUDIO ; 
 int OBS_SOURCE_COMPOSITE ; 

__attribute__((used)) static inline bool source_has_audio(obs_source_t *source)
{
	return (source->info.output_flags &
		(OBS_SOURCE_AUDIO | OBS_SOURCE_COMPOSITE)) != 0;
}