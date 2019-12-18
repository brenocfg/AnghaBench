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
typedef  int /*<<< orphan*/  obs_encoder_t ;
struct TYPE_3__ {int /*<<< orphan*/  encoders_mutex; int /*<<< orphan*/  first_encoder; } ;
struct TYPE_4__ {TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/ * get_context_by_name (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* obs ; 
 int /*<<< orphan*/  obs_encoder_addref_safe_ ; 

obs_encoder_t *obs_get_encoder_by_name(const char *name)
{
	if (!obs)
		return NULL;
	return get_context_by_name(&obs->data.first_encoder, name,
				   &obs->data.encoders_mutex,
				   obs_encoder_addref_safe_);
}