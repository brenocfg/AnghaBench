#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* pause ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {TYPE_2__ context; TYPE_1__ info; } ;
typedef  TYPE_3__ obs_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_output_valid (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void obs_output_pause(obs_output_t *output)
{
	if (!obs_output_valid(output, "obs_output_pause"))
		return;

	if (output->info.pause)
		output->info.pause(output->context.data);
}