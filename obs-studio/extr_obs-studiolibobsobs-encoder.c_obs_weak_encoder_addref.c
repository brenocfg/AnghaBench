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
struct TYPE_3__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ obs_weak_encoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_weak_ref_addref (int /*<<< orphan*/ *) ; 

void obs_weak_encoder_addref(obs_weak_encoder_t *weak)
{
	if (!weak)
		return;

	obs_weak_ref_addref(&weak->ref);
}