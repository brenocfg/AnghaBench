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
struct TYPE_2__ {int stlink_v; } ;
struct stlink_libusb {int protocoll; int ep_rep; int ep_req; scalar_t__ libusb_ctx; TYPE_1__ version; int /*<<< orphan*/  cmd_len; scalar_t__ sg_transfer_idx; struct libusb_device_handle* usb_handle; int /*<<< orphan*/  serial_size; scalar_t__ serial; int /*<<< orphan*/  core_stat; struct stlink_libusb* backend_data; } ;
struct libusb_device_handle {int dummy; } ;
struct libusb_device_descriptor {scalar_t__ idVendor; scalar_t__ idProduct; int /*<<< orphan*/  iSerialNumber; } ;
typedef  struct stlink_libusb stlink_t ;
typedef  int /*<<< orphan*/  libusb_device ;

/* Variables and functions */
 int LIBUSB_ENDPOINT_IN ; 
 int LIBUSB_ENDPOINT_OUT ; 
 int /*<<< orphan*/  STLINK_CMD_SIZE ; 
 int /*<<< orphan*/  STLINK_CORE_STAT_UNKNOWN ; 
 scalar_t__ STLINK_DEV_DEBUG_MODE ; 
 scalar_t__ STLINK_DEV_DFU_MODE ; 
 int /*<<< orphan*/  STLINK_SG_SIZE ; 
 int /*<<< orphan*/  STLINK_SWDCLK_1P8MHZ_DIVISOR ; 
 scalar_t__ STLINK_USB_PID_STLINK ; 
 scalar_t__ STLINK_USB_PID_STLINK_32L ; 
 scalar_t__ STLINK_USB_PID_STLINK_NUCLEO ; 
 scalar_t__ STLINK_USB_VID_ST ; 
 int atoi (char*) ; 
 struct stlink_libusb* calloc (int,int) ; 
 int errno ; 
 int /*<<< orphan*/  free (struct stlink_libusb*) ; 
 char* getenv (char*) ; 
 scalar_t__ libusb_claim_interface (struct libusb_device_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libusb_close (struct libusb_device_handle*) ; 
 int libusb_detach_kernel_driver (struct libusb_device_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libusb_exit (scalar_t__) ; 
 int /*<<< orphan*/  libusb_free_device_list (int /*<<< orphan*/ **,int) ; 
 int libusb_get_bus_number (int /*<<< orphan*/ *) ; 
 scalar_t__ libusb_get_configuration (struct libusb_device_handle*,int*) ; 
 int libusb_get_device_address (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libusb_get_device_descriptor (int /*<<< orphan*/ *,struct libusb_device_descriptor*) ; 
 scalar_t__ libusb_get_device_list (scalar_t__,int /*<<< orphan*/ ***) ; 
 int /*<<< orphan*/  libusb_get_string_descriptor_ascii (struct libusb_device_handle*,int /*<<< orphan*/ ,unsigned char*,int) ; 
 scalar_t__ libusb_init (scalar_t__*) ; 
 int libusb_kernel_driver_active (struct libusb_device_handle*,int /*<<< orphan*/ ) ; 
 int libusb_open (int /*<<< orphan*/ *,struct libusb_device_handle**) ; 
 scalar_t__ libusb_set_configuration (struct libusb_device_handle*,int) ; 
 scalar_t__ memcmp (char*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stlink_close (struct stlink_libusb*) ; 
 scalar_t__ stlink_current_mode (struct stlink_libusb*) ; 
 int /*<<< orphan*/  stlink_enter_swd_mode (struct stlink_libusb*) ; 
 int /*<<< orphan*/  stlink_exit_dfu_mode (struct stlink_libusb*) ; 
 int /*<<< orphan*/  stlink_jtag_reset (struct stlink_libusb*,int) ; 
 int stlink_load_device_params (struct stlink_libusb*) ; 
 int /*<<< orphan*/  stlink_reset (struct stlink_libusb*) ; 
 int /*<<< orphan*/  stlink_set_swdclk (struct stlink_libusb*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  usleep (int) ; 

stlink_t *stlink_open_usb(bool reset, char serial[16]) {
  stlink_t *sl = NULL;
  struct stlink_libusb *slu = NULL;
  int ret = -1;
  int config;

  sl = calloc(1, sizeof(stlink_t));
  slu = calloc(1, sizeof(struct stlink_libusb));
  if (sl == NULL) goto on_malloc_error;
  if (slu == NULL) goto on_malloc_error;

  sl->backend_data = slu;

  sl->core_stat = STLINK_CORE_STAT_UNKNOWN;
  if (libusb_init(&(slu->libusb_ctx))) {
    printf("failed to init libusb context, wrong version of libraries?\n");
    goto on_error;
  }

  libusb_device **list;
  /** @todo We should use ssize_t and use it as a counter if > 0. As per libusb
   * API: ssize_t libusb_get_device_list (libusb_context *ctx, libusb_device
   * ***list) */
  int cnt = (int) libusb_get_device_list(slu->libusb_ctx, &list);
  struct libusb_device_descriptor desc;
  int devBus = 0;
  int devAddr = 0;

  /* @TODO: Reading a environment variable in a usb open function is not very
    nice, this
    should be refactored and moved into the CLI tools, and instead of giving
    USB_BUS:USB_ADDR a real stlink
    serial string should be passed to this function. Probably people are using
    this but this is very odd because
    as programmer can change to multiple busses and it is better to detect them
    based on serial.  */
  char *device = getenv("STLINK_DEVICE");
  if (device) {
    char *c = strchr(device, ':');
    if (c == NULL) {
      printf("STLINK_DEVICE must be <USB_BUS>:<USB_ADDR> format\n");
      goto on_error;
    }
    devBus = atoi(device);
    *c++ = 0;
    devAddr = atoi(c);
    printf("bus %03d dev %03d\n", devBus, devAddr);
  }

  while (cnt--) {
    libusb_get_device_descriptor(list[cnt], &desc);
    if (desc.idVendor != STLINK_USB_VID_ST) continue;

    if (devBus && devAddr) {
      if ((libusb_get_bus_number(list[cnt]) != devBus) ||
          (libusb_get_device_address(list[cnt]) != devAddr)) {
        continue;
      }
    }

    if ((desc.idProduct == STLINK_USB_PID_STLINK_32L) ||
        (desc.idProduct == STLINK_USB_PID_STLINK_NUCLEO)) {
      struct libusb_device_handle *handle;

      ret = libusb_open(list[cnt], &handle);
      if (ret) continue;

      sl->serial_size = libusb_get_string_descriptor_ascii(
          handle, desc.iSerialNumber, (unsigned char *) sl->serial,
          sizeof(sl->serial));
      libusb_close(handle);

      if ((serial == NULL) || (*serial == 0)) break;

      if (sl->serial_size < 0) continue;

      if (memcmp(serial, &sl->serial, sl->serial_size) == 0) break;

      continue;
    }

    if (desc.idProduct == STLINK_USB_PID_STLINK) {
      slu->protocoll = 1;
      break;
    }
  }

  if (cnt < 0) {
    printf("Couldn't find %s ST-Link/V2 devices\n",
           (devBus && devAddr) ? "matched" : "any");
    goto on_error;
  } else {
    ret = libusb_open(list[cnt], &slu->usb_handle);
    if (ret != 0) {
      printf("Error %d (%s) opening ST-Link/V2 device %03d:%03d\n", ret,
             strerror(errno), libusb_get_bus_number(list[cnt]),
             libusb_get_device_address(list[cnt]));
      goto on_error;
    }
  }

  libusb_free_device_list(list, 1);

  if (libusb_kernel_driver_active(slu->usb_handle, 0) == 1) {
    ret = libusb_detach_kernel_driver(slu->usb_handle, 0);
    if (ret < 0) {
      printf("libusb_detach_kernel_driver(() error %s\n", strerror(-ret));
      goto on_libusb_error;
    }
  }

  if (libusb_get_configuration(slu->usb_handle, &config)) {
    /* this may fail for a previous configured device */
    printf("libusb_get_configuration()\n");
    goto on_libusb_error;
  }

  if (config != 1) {
    printf("setting new configuration (%d -> 1)\n", config);
    if (libusb_set_configuration(slu->usb_handle, 1)) {
      /* this may fail for a previous configured device */
      printf("libusb_set_configuration() failed\n");
      goto on_libusb_error;
    }
  }

  if (libusb_claim_interface(slu->usb_handle, 0)) {
    printf(
        "Stlink usb device found, but unable to claim (probably already in "
        "use?)\n");
    goto on_libusb_error;
  }

  // TODO - could use the scanning techniq from stm8 code here...
  slu->ep_rep = 1 /* ep rep */ | LIBUSB_ENDPOINT_IN;
  if (desc.idProduct == STLINK_USB_PID_STLINK_NUCLEO) {
    slu->ep_req = 1 /* ep req */ | LIBUSB_ENDPOINT_OUT;
  } else {
    slu->ep_req = 2 /* ep req */ | LIBUSB_ENDPOINT_OUT;
  }

  slu->sg_transfer_idx = 0;
  // TODO - never used at the moment, always CMD_SIZE
  slu->cmd_len = (slu->protocoll == 1) ? STLINK_SG_SIZE : STLINK_CMD_SIZE;

  if (stlink_current_mode(sl) == STLINK_DEV_DFU_MODE) {
    printf("-- exit_dfu_mode\n");
    stlink_exit_dfu_mode(sl);
  }

  if (stlink_current_mode(sl) != STLINK_DEV_DEBUG_MODE) {
    stlink_enter_swd_mode(sl);
  }

  sl->version.stlink_v = 2;

  if (reset) {
    if (sl->version.stlink_v > 1) stlink_jtag_reset(sl, 2);
    stlink_reset(sl);
    usleep(10000);
  }

  ret = stlink_load_device_params(sl);

  // Set the stlink clock speed (default is 1800kHz)
  stlink_set_swdclk(sl, STLINK_SWDCLK_1P8MHZ_DIVISOR);

on_libusb_error:
  if (ret == -1) {
    stlink_close(sl);
    return NULL;
  }

  return sl;

on_error:
  if (slu->libusb_ctx) libusb_exit(slu->libusb_ctx);

on_malloc_error:
  if (sl != NULL) free(sl);
  if (slu != NULL) free(slu);

  return NULL;
}