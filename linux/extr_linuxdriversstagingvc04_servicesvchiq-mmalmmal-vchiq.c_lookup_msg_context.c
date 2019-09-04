#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vchiq_mmal_instance {int /*<<< orphan*/  context_map; } ;
struct mmal_msg_context {int dummy; } ;

/* Variables and functions */
 struct mmal_msg_context* idr_find (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct mmal_msg_context *
lookup_msg_context(struct vchiq_mmal_instance *instance, int handle)
{
	return idr_find(&instance->context_map, handle);
}