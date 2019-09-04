#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  obs_data_t ;
struct TYPE_3__ {int /*<<< orphan*/  private_data; } ;
struct TYPE_4__ {TYPE_1__ data; } ;

/* Variables and functions */
 TYPE_2__* obs ; 
 int /*<<< orphan*/  obs_data_apply (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void obs_apply_private_data(obs_data_t *settings)
{
	if (!obs || !settings)
		return;

	obs_data_apply(obs->data.private_data, settings);
}