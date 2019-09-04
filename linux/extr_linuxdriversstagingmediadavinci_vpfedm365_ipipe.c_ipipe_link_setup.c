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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct vpfe_ipipe_device {int /*<<< orphan*/  output; int /*<<< orphan*/  input; } ;
struct TYPE_2__ {int /*<<< orphan*/  input; } ;
struct vpfe_device {TYPE_1__ vpfe_ipipeif; } ;
struct v4l2_subdev {int dummy; } ;
struct media_pad {int index; int /*<<< orphan*/  entity; } ;
struct media_entity {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  IPIPEIF_INPUT_MEMORY ; 
 int /*<<< orphan*/  IPIPE_INPUT_CCDC ; 
 int /*<<< orphan*/  IPIPE_INPUT_MEMORY ; 
 int /*<<< orphan*/  IPIPE_INPUT_NONE ; 
 int /*<<< orphan*/  IPIPE_OUTPUT_NONE ; 
 int /*<<< orphan*/  IPIPE_OUTPUT_RESIZER ; 
#define  IPIPE_PAD_SINK 129 
#define  IPIPE_PAD_SOURCE 128 
 int MEDIA_LNK_FL_ENABLED ; 
 int /*<<< orphan*/  is_media_entity_v4l2_subdev (int /*<<< orphan*/ ) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (struct media_entity*) ; 
 struct vpfe_device* to_vpfe_device (struct vpfe_ipipe_device*) ; 
 struct vpfe_ipipe_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int
ipipe_link_setup(struct media_entity *entity, const struct media_pad *local,
		     const struct media_pad *remote, u32 flags)
{
	struct v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	struct vpfe_ipipe_device *ipipe = v4l2_get_subdevdata(sd);
	struct vpfe_device *vpfe_dev = to_vpfe_device(ipipe);
	u16 ipipeif_sink = vpfe_dev->vpfe_ipipeif.input;

	if (!is_media_entity_v4l2_subdev(remote->entity))
		return -EINVAL;

	switch (local->index) {
	case IPIPE_PAD_SINK:
		if (!(flags & MEDIA_LNK_FL_ENABLED)) {
			ipipe->input = IPIPE_INPUT_NONE;
			break;
		}
		if (ipipe->input != IPIPE_INPUT_NONE)
			return -EBUSY;
		if (ipipeif_sink == IPIPEIF_INPUT_MEMORY)
			ipipe->input = IPIPE_INPUT_MEMORY;
		else
			ipipe->input = IPIPE_INPUT_CCDC;
		break;

	case IPIPE_PAD_SOURCE:
		/* out to RESIZER */
		if (flags & MEDIA_LNK_FL_ENABLED)
			ipipe->output = IPIPE_OUTPUT_RESIZER;
		else
			ipipe->output = IPIPE_OUTPUT_NONE;
		break;

	default:
		return -EINVAL;
	}

	return 0;
}