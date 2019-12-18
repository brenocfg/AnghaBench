#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  private; } ;
struct TYPE_9__ {TYPE_1__ context; } ;
typedef  TYPE_2__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  duplicate_filters (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_valid (TYPE_2__*,char*) ; 

void obs_source_copy_filters(obs_source_t *dst, obs_source_t *src)
{
	if (!obs_source_valid(dst, "obs_source_copy_filters"))
		return;
	if (!obs_source_valid(src, "obs_source_copy_filters"))
		return;

	duplicate_filters(dst, src, dst->context.private);
}