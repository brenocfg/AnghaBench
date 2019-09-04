#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_4__ context; } ;
typedef  TYPE_1__ obs_encoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_context_data_setname (TYPE_4__*,char const*) ; 
 int /*<<< orphan*/  obs_encoder_valid (TYPE_1__*,char*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

void obs_encoder_set_name(obs_encoder_t *encoder, const char *name)
{
	if (!obs_encoder_valid(encoder, "obs_encoder_set_name"))
		return;

	if (name && *name && strcmp(name, encoder->context.name) != 0)
		obs_context_data_setname(&encoder->context, name);
}