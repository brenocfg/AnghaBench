#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct packet   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct fb_info {int /*<<< orphan*/  device; } ;
struct TYPE_6__ {int bits_per_pixel; int /*<<< orphan*/  red; int /*<<< orphan*/  green; int /*<<< orphan*/  blue; int /*<<< orphan*/  transp; } ;
struct TYPE_7__ {TYPE_1__ var; } ;
struct bcm2708_fb {unsigned int* gpu_cmap; int* cmap; TYPE_2__ fb; int /*<<< orphan*/  fw; } ;
struct packet {unsigned int offset; unsigned int length; unsigned int* cmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RPI_FIRMWARE_FRAMEBUFFER_SET_PALETTE ; 
 int convert_bitfield (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,unsigned int) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 TYPE_3__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned int*,unsigned int*,int) ; 
 int rpi_firmware_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 struct bcm2708_fb* to_bcm2708 (struct fb_info*) ; 

__attribute__((used)) static int bcm2708_fb_setcolreg(unsigned int regno, unsigned int red,
				unsigned int green, unsigned int blue,
				unsigned int transp, struct fb_info *info)
{
	struct bcm2708_fb *fb = to_bcm2708(info);

	if (fb->fb.var.bits_per_pixel <= 8) {
		if (regno < 256) {
			/* blue [23:16], green [15:8], red [7:0] */
			fb->gpu_cmap[regno] = ((red   >> 8) & 0xff) << 0 |
					      ((green >> 8) & 0xff) << 8 |
					      ((blue  >> 8) & 0xff) << 16;
		}
		/* Hack: we need to tell GPU the palette has changed, but
		 * currently bcm2708_fb_set_par takes noticeable time when
		 * called for every (256) colour
		 * So just call it for what looks like the last colour in a
		 * list for now.
		 */
		if (regno == 15 || regno == 255) {
			struct packet {
				u32 offset;
				u32 length;
				u32 cmap[256];
			} *packet;
			int ret;

			packet = kmalloc(sizeof(*packet), GFP_KERNEL);
			if (!packet)
				return -ENOMEM;
			packet->offset = 0;
			packet->length = regno + 1;
			memcpy(packet->cmap, fb->gpu_cmap,
			       sizeof(packet->cmap));
			ret = rpi_firmware_property(fb->fw,
						    RPI_FIRMWARE_FRAMEBUFFER_SET_PALETTE,
						    packet,
						    (2 + packet->length) * sizeof(u32));
			if (ret || packet->offset)
				dev_err(info->device,
					"Failed to set palette (%d,%u)\n",
					ret, packet->offset);
			kfree(packet);
		}
	} else if (regno < 16) {
		fb->cmap[regno] = convert_bitfield(transp, &fb->fb.var.transp) |
				  convert_bitfield(blue, &fb->fb.var.blue) |
				  convert_bitfield(green, &fb->fb.var.green) |
				  convert_bitfield(red, &fb->fb.var.red);
	}
	return regno > 255;
}