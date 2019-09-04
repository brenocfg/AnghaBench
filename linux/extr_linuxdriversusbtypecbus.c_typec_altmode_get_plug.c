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
struct typec_altmode {int /*<<< orphan*/  dev; } ;
struct altmode {TYPE_1__** plug; } ;
typedef  enum typec_plug_index { ____Placeholder_typec_plug_index } typec_plug_index ;
struct TYPE_4__ {struct altmode* partner; } ;
struct TYPE_3__ {struct typec_altmode adev; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 TYPE_2__* to_altmode (struct typec_altmode*) ; 

struct typec_altmode *typec_altmode_get_plug(struct typec_altmode *adev,
					     enum typec_plug_index index)
{
	struct altmode *port = to_altmode(adev)->partner;

	if (port->plug[index]) {
		get_device(&port->plug[index]->adev.dev);
		return &port->plug[index]->adev;
	}

	return NULL;
}