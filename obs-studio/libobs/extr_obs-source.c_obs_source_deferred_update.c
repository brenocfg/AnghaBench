#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  settings; scalar_t__ data; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* update ) (scalar_t__,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int defer_update; TYPE_2__ context; TYPE_1__ info; } ;
typedef  TYPE_3__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void obs_source_deferred_update(obs_source_t *source)
{
	if (source->context.data && source->info.update)
		source->info.update(source->context.data,
				    source->context.settings);

	source->defer_update = false;
}