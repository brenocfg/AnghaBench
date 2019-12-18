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
typedef  int /*<<< orphan*/  obs_weak_source_t ;
struct TYPE_3__ {int /*<<< orphan*/ * control; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_weak_source_addref (int /*<<< orphan*/ *) ; 

obs_weak_source_t *obs_source_get_weak_source(obs_source_t *source)
{
	if (!source)
		return NULL;

	obs_weak_source_t *weak = source->control;
	obs_weak_source_addref(weak);
	return weak;
}