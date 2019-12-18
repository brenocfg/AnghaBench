#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  settings; int /*<<< orphan*/  data; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* load ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {TYPE_2__ context; TYPE_1__ info; } ;
typedef  TYPE_3__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  data_valid (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  obs_source_dosignal (TYPE_3__*,char*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void obs_source_load(obs_source_t *source)
{
	if (!data_valid(source, "obs_source_load"))
		return;
	if (source->info.load)
		source->info.load(source->context.data,
				  source->context.settings);

	obs_source_dosignal(source, "source_load", "load");
}