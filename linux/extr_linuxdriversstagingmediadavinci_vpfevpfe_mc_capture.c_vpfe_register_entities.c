#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_15__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_11__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ num_pads; } ;
struct TYPE_21__ {TYPE_15__ entity; } ;
struct TYPE_27__ {TYPE_2__ subdev; } ;
struct TYPE_23__ {TYPE_15__ entity; } ;
struct TYPE_17__ {TYPE_4__ subdev; } ;
struct TYPE_22__ {TYPE_15__ entity; } ;
struct TYPE_18__ {TYPE_3__ subdev; } ;
struct TYPE_24__ {TYPE_15__ entity; } ;
struct TYPE_25__ {TYPE_5__ subdev; } ;
struct TYPE_26__ {TYPE_6__ crop_resizer; } ;
struct vpfe_device {int num_ext_subdevs; TYPE_9__ vpfe_isif; TYPE_11__ vpfe_ipipeif; TYPE_13__ vpfe_ipipe; TYPE_7__ vpfe_resizer; int /*<<< orphan*/  v4l2_dev; TYPE_1__** sd; } ;
struct TYPE_20__ {TYPE_15__ entity; } ;

/* Variables and functions */
 int media_create_pad_link (TYPE_15__*,int,TYPE_15__*,int /*<<< orphan*/ ,unsigned int) ; 
 int register_i2c_devices (struct vpfe_device*) ; 
 int v4l2_device_register_subdev_nodes (int /*<<< orphan*/ *) ; 
 int vpfe_ipipe_register_entities (TYPE_13__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vpfe_ipipe_unregister_entities (TYPE_13__*) ; 
 int vpfe_ipipeif_register_entities (TYPE_11__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vpfe_ipipeif_unregister_entities (TYPE_11__*) ; 
 int vpfe_isif_register_entities (TYPE_9__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vpfe_isif_unregister_entities (TYPE_9__*) ; 
 int vpfe_resizer_register_entities (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vpfe_resizer_unregister_entities (TYPE_7__*) ; 

__attribute__((used)) static int vpfe_register_entities(struct vpfe_device *vpfe_dev)
{
	unsigned int flags = 0;
	int ret;
	int i;

	/* register i2c devices first */
	ret = register_i2c_devices(vpfe_dev);
	if (ret)
		return ret;

	/* register rest of the sub-devs */
	ret = vpfe_isif_register_entities(&vpfe_dev->vpfe_isif,
					  &vpfe_dev->v4l2_dev);
	if (ret)
		return ret;

	ret = vpfe_ipipeif_register_entities(&vpfe_dev->vpfe_ipipeif,
					     &vpfe_dev->v4l2_dev);
	if (ret)
		goto out_isif_register;

	ret = vpfe_ipipe_register_entities(&vpfe_dev->vpfe_ipipe,
					   &vpfe_dev->v4l2_dev);
	if (ret)
		goto out_ipipeif_register;

	ret = vpfe_resizer_register_entities(&vpfe_dev->vpfe_resizer,
					     &vpfe_dev->v4l2_dev);
	if (ret)
		goto out_ipipe_register;

	/* create links now, starting with external(i2c) entities */
	for (i = 0; i < vpfe_dev->num_ext_subdevs; i++)
		/*
		 * if entity has no pads (ex: amplifier),
		 * can't establish link
		 */
		if (vpfe_dev->sd[i]->entity.num_pads) {
			ret = media_create_pad_link(&vpfe_dev->sd[i]->entity,
				0, &vpfe_dev->vpfe_isif.subdev.entity,
				0, flags);
			if (ret < 0)
				goto out_resizer_register;
		}

	ret = media_create_pad_link(&vpfe_dev->vpfe_isif.subdev.entity, 1,
				       &vpfe_dev->vpfe_ipipeif.subdev.entity,
				       0, flags);
	if (ret < 0)
		goto out_resizer_register;

	ret = media_create_pad_link(&vpfe_dev->vpfe_ipipeif.subdev.entity, 1,
				       &vpfe_dev->vpfe_ipipe.subdev.entity,
				       0, flags);
	if (ret < 0)
		goto out_resizer_register;

	ret = media_create_pad_link(&vpfe_dev->vpfe_ipipe.subdev.entity,
			1, &vpfe_dev->vpfe_resizer.crop_resizer.subdev.entity,
			0, flags);
	if (ret < 0)
		goto out_resizer_register;

	ret = media_create_pad_link(&vpfe_dev->vpfe_ipipeif.subdev.entity, 1,
			&vpfe_dev->vpfe_resizer.crop_resizer.subdev.entity,
			0, flags);
	if (ret < 0)
		goto out_resizer_register;

	ret = v4l2_device_register_subdev_nodes(&vpfe_dev->v4l2_dev);
	if (ret < 0)
		goto out_resizer_register;

	return 0;

out_resizer_register:
	vpfe_resizer_unregister_entities(&vpfe_dev->vpfe_resizer);
out_ipipe_register:
	vpfe_ipipe_unregister_entities(&vpfe_dev->vpfe_ipipe);
out_ipipeif_register:
	vpfe_ipipeif_unregister_entities(&vpfe_dev->vpfe_ipipeif);
out_isif_register:
	vpfe_isif_unregister_entities(&vpfe_dev->vpfe_isif);

	return ret;
}