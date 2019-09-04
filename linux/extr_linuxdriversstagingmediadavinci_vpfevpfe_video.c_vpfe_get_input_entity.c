#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vpfe_video_device {struct vpfe_device* vpfe_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * pads; } ;
struct vpfe_device {TYPE_1__ vpfe_isif; } ;
struct media_pad {struct media_entity* entity; } ;
struct media_entity {int dummy; } ;

/* Variables and functions */
 struct media_pad* media_entity_remote_pad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static struct media_entity *vpfe_get_input_entity
			(struct vpfe_video_device *video)
{
	struct vpfe_device *vpfe_dev = video->vpfe_dev;
	struct media_pad *remote;

	remote = media_entity_remote_pad(&vpfe_dev->vpfe_isif.pads[0]);
	if (!remote) {
		pr_err("Invalid media connection to isif/ccdc\n");
		return NULL;
	}
	return remote->entity;
}