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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct usb_interface {int /*<<< orphan*/  dev; int /*<<< orphan*/  cur_altsetting; } ;
struct dlfb_data {int sku_pixel_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_VENDOR_DESCRIPTOR_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_get_descriptor (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_get_extra_descriptor (int /*<<< orphan*/ ,int,char**) ; 

__attribute__((used)) static int dlfb_parse_vendor_descriptor(struct dlfb_data *dlfb,
					struct usb_interface *intf)
{
	char *desc;
	char *buf;
	char *desc_end;
	int total_len;

	buf = kzalloc(MAX_VENDOR_DESCRIPTOR_SIZE, GFP_KERNEL);
	if (!buf)
		return false;
	desc = buf;

	total_len = usb_get_descriptor(interface_to_usbdev(intf),
					0x5f, /* vendor specific */
					0, desc, MAX_VENDOR_DESCRIPTOR_SIZE);

	/* if not found, look in configuration descriptor */
	if (total_len < 0) {
		if (0 == usb_get_extra_descriptor(intf->cur_altsetting,
			0x5f, &desc))
			total_len = (int) desc[0];
	}

	if (total_len > 5) {
		dev_info(&intf->dev,
			 "vendor descriptor length: %d data: %11ph\n",
			 total_len, desc);

		if ((desc[0] != total_len) || /* descriptor length */
		    (desc[1] != 0x5f) ||   /* vendor descriptor type */
		    (desc[2] != 0x01) ||   /* version (2 bytes) */
		    (desc[3] != 0x00) ||
		    (desc[4] != total_len - 2)) /* length after type */
			goto unrecognized;

		desc_end = desc + total_len;
		desc += 5; /* the fixed header we've already parsed */

		while (desc < desc_end) {
			u8 length;
			u16 key;

			key = *desc++;
			key |= (u16)*desc++ << 8;
			length = *desc++;

			switch (key) {
			case 0x0200: { /* max_area */
				u32 max_area = *desc++;
				max_area |= (u32)*desc++ << 8;
				max_area |= (u32)*desc++ << 16;
				max_area |= (u32)*desc++ << 24;
				dev_warn(&intf->dev,
					 "DL chip limited to %d pixel modes\n",
					 max_area);
				dlfb->sku_pixel_limit = max_area;
				break;
			}
			default:
				break;
			}
			desc += length;
		}
	} else {
		dev_info(&intf->dev, "vendor descriptor not available (%d)\n",
			 total_len);
	}

	goto success;

unrecognized:
	/* allow udlfb to load for now even if firmware unrecognized */
	dev_err(&intf->dev, "Unrecognized vendor firmware descriptor\n");

success:
	kfree(buf);
	return true;
}