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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_mbus_code_enum {int pad; size_t index; int /*<<< orphan*/  code; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  code; } ;
struct iss_ipipeif_device {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
#define  IPIPEIF_PAD_SINK 130 
#define  IPIPEIF_PAD_SOURCE_ISIF_SF 129 
#define  IPIPEIF_PAD_SOURCE_VP 128 
 struct v4l2_mbus_framefmt* __ipipeif_get_format (struct iss_ipipeif_device*,struct v4l2_subdev_pad_config*,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ipipeif_fmts ; 
 struct iss_ipipeif_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ipipeif_enum_mbus_code(struct v4l2_subdev *sd,
				  struct v4l2_subdev_pad_config *cfg,
				  struct v4l2_subdev_mbus_code_enum *code)
{
	struct iss_ipipeif_device *ipipeif = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;

	switch (code->pad) {
	case IPIPEIF_PAD_SINK:
		if (code->index >= ARRAY_SIZE(ipipeif_fmts))
			return -EINVAL;

		code->code = ipipeif_fmts[code->index];
		break;

	case IPIPEIF_PAD_SOURCE_ISIF_SF:
	case IPIPEIF_PAD_SOURCE_VP:
		/* No format conversion inside IPIPEIF */
		if (code->index != 0)
			return -EINVAL;

		format = __ipipeif_get_format(ipipeif, cfg, IPIPEIF_PAD_SINK,
					      code->which);

		code->code = format->code;
		break;

	default:
		return -EINVAL;
	}

	return 0;
}