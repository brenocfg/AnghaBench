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
struct stinger_info {scalar_t__ media_source; int /*<<< orphan*/  source; } ;
typedef  int /*<<< orphan*/  (* obs_source_enum_proc_t ) (int /*<<< orphan*/ ,scalar_t__,void*) ;

/* Variables and functions */

__attribute__((used)) static void stinger_enum_all_sources(void *data,
				     obs_source_enum_proc_t enum_callback,
				     void *param)
{
	struct stinger_info *s = data;
	if (s->media_source)
		enum_callback(s->source, s->media_source, param);
}