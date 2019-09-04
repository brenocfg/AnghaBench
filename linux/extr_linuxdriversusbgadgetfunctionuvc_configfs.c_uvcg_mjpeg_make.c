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
struct config_group {int dummy; } ;
struct TYPE_4__ {struct config_group group; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int bDefaultFrameIndex; scalar_t__ bCopyProtect; scalar_t__ bmInterfaceFlags; scalar_t__ bAspectRatioY; scalar_t__ bAspectRatioX; int /*<<< orphan*/  bDescriptorSubType; int /*<<< orphan*/  bDescriptorType; int /*<<< orphan*/  bLength; } ;
struct uvcg_mjpeg {TYPE_2__ fmt; TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct config_group* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_DT_CS_INTERFACE ; 
 int /*<<< orphan*/  UVCG_MJPEG ; 
 int /*<<< orphan*/  UVC_DT_FORMAT_MJPEG_SIZE ; 
 int /*<<< orphan*/  UVC_VS_FORMAT_MJPEG ; 
 int /*<<< orphan*/  config_group_init_type_name (struct config_group*,char const*,int /*<<< orphan*/ *) ; 
 struct uvcg_mjpeg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvcg_mjpeg_type ; 

__attribute__((used)) static struct config_group *uvcg_mjpeg_make(struct config_group *group,
						   const char *name)
{
	struct uvcg_mjpeg *h;

	h = kzalloc(sizeof(*h), GFP_KERNEL);
	if (!h)
		return ERR_PTR(-ENOMEM);

	h->desc.bLength			= UVC_DT_FORMAT_MJPEG_SIZE;
	h->desc.bDescriptorType		= USB_DT_CS_INTERFACE;
	h->desc.bDescriptorSubType	= UVC_VS_FORMAT_MJPEG;
	h->desc.bDefaultFrameIndex	= 1;
	h->desc.bAspectRatioX		= 0;
	h->desc.bAspectRatioY		= 0;
	h->desc.bmInterfaceFlags	= 0;
	h->desc.bCopyProtect		= 0;

	h->fmt.type = UVCG_MJPEG;
	config_group_init_type_name(&h->fmt.group, name,
				    &uvcg_mjpeg_type);

	return &h->fmt.group;
}