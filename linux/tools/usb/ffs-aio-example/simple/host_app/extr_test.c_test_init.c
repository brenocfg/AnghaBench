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
struct test_state {int attached; int /*<<< orphan*/ * ctx; int /*<<< orphan*/ * handle; int /*<<< orphan*/ * found; } ;
struct libusb_device_descriptor {scalar_t__ idVendor; scalar_t__ idProduct; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  libusb_device ;

/* Variables and functions */
 scalar_t__ PRODUCT ; 
 scalar_t__ VENDOR ; 
 int /*<<< orphan*/  libusb_attach_kernel_driver (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int libusb_claim_interface (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libusb_close (int /*<<< orphan*/ *) ; 
 int libusb_detach_kernel_driver (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* libusb_error_name (int) ; 
 int /*<<< orphan*/  libusb_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libusb_free_device_list (int /*<<< orphan*/ **,int) ; 
 int libusb_get_device_descriptor (int /*<<< orphan*/ *,struct libusb_device_descriptor*) ; 
 int libusb_get_device_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ***) ; 
 int libusb_init (int /*<<< orphan*/ **) ; 
 int libusb_open (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int test_init(struct test_state *state)
{
	int i, ret;
	ssize_t cnt;
	libusb_device **list;

	state->found = NULL;
	state->ctx = NULL;
	state->handle = NULL;
	state->attached = 0;

	ret = libusb_init(&state->ctx);
	if (ret) {
		printf("cannot init libusb: %s\n", libusb_error_name(ret));
		return 1;
	}

	cnt = libusb_get_device_list(state->ctx, &list);
	if (cnt <= 0) {
		printf("no devices found\n");
		goto error1;
	}

	for (i = 0; i < cnt; ++i) {
		libusb_device *dev = list[i];
		struct libusb_device_descriptor desc;
		ret = libusb_get_device_descriptor(dev, &desc);
		if (ret) {
			printf("unable to get device descriptor: %s\n",
			       libusb_error_name(ret));
			goto error2;
		}
		if (desc.idVendor == VENDOR && desc.idProduct == PRODUCT) {
			state->found = dev;
			break;
		}
	}

	if (!state->found) {
		printf("no devices found\n");
		goto error2;
	}

	ret = libusb_open(state->found, &state->handle);
	if (ret) {
		printf("cannot open device: %s\n", libusb_error_name(ret));
		goto error2;
	}

	if (libusb_claim_interface(state->handle, 0)) {
		ret = libusb_detach_kernel_driver(state->handle, 0);
		if (ret) {
			printf("unable to detach kernel driver: %s\n",
			       libusb_error_name(ret));
			goto error3;
		}
		state->attached = 1;
		ret = libusb_claim_interface(state->handle, 0);
		if (ret) {
			printf("cannot claim interface: %s\n",
			       libusb_error_name(ret));
			goto error4;
		}
	}

	return 0;

error4:
	if (state->attached == 1)
		libusb_attach_kernel_driver(state->handle, 0);

error3:
	libusb_close(state->handle);

error2:
	libusb_free_device_list(list, 1);

error1:
	libusb_exit(state->ctx);
	return 1;
}