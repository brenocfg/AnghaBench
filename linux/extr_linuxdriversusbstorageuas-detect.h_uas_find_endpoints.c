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
struct TYPE_2__ {unsigned int bNumEndpoints; } ;
struct usb_host_interface {TYPE_1__ desc; struct usb_host_endpoint* endpoint; } ;
struct usb_host_endpoint {unsigned char* extra; int extralen; } ;

/* Variables and functions */
 int ENODEV ; 
 unsigned char USB_DT_PIPE_USAGE ; 

__attribute__((used)) static int uas_find_endpoints(struct usb_host_interface *alt,
			      struct usb_host_endpoint *eps[])
{
	struct usb_host_endpoint *endpoint = alt->endpoint;
	unsigned i, n_endpoints = alt->desc.bNumEndpoints;

	for (i = 0; i < n_endpoints; i++) {
		unsigned char *extra = endpoint[i].extra;
		int len = endpoint[i].extralen;
		while (len >= 3) {
			if (extra[1] == USB_DT_PIPE_USAGE) {
				unsigned pipe_id = extra[2];
				if (pipe_id > 0 && pipe_id < 5)
					eps[pipe_id - 1] = &endpoint[i];
				break;
			}
			len -= extra[0];
			extra += extra[0];
		}
	}

	if (!eps[0] || !eps[1] || !eps[2] || !eps[3])
		return -ENODEV;

	return 0;
}