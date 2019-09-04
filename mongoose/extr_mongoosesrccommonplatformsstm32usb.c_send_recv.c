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
struct stlink_libusb {int protocoll; int /*<<< orphan*/  sg_transfer_idx; int /*<<< orphan*/  ep_rep; int /*<<< orphan*/  usb_handle; int /*<<< orphan*/  ep_req; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int libusb_bulk_transfer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int,int*,int) ; 
 char* libusb_error_name (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

ssize_t send_recv(struct stlink_libusb *handle, int terminate,
                  unsigned char *txbuf, size_t txsize, unsigned char *rxbuf,
                  size_t rxsize) {
  /* note: txbuf and rxbuf can point to the same area */
  int res = 0;
  int t;

  t = libusb_bulk_transfer(handle->usb_handle, handle->ep_req, txbuf,
                           (int) txsize, &res, 3000);
  if (t) {
    printf("[!] send_recv send request failed: %s\n", libusb_error_name(t));
    return -1;
  } else if ((size_t) res != txsize) {
    printf("[!] send_recv send request wrote %u bytes (instead of %u).\n",
           (unsigned int) res, (unsigned int) txsize);
  }

  if (rxsize != 0) {
    t = libusb_bulk_transfer(handle->usb_handle, handle->ep_rep, rxbuf,
                             (int) rxsize, &res, 3000);
    if (t) {
      printf("[!] send_recv read reply failed: %s\n", libusb_error_name(t));
      return -1;
    }
  }

  if ((handle->protocoll == 1) && terminate) {
    /* Read the SG reply */
    unsigned char sg_buf[13];
    t = libusb_bulk_transfer(handle->usb_handle, handle->ep_rep, sg_buf, 13,
                             &res, 3000);
    if (t) {
      printf("[!] send_recv read storage failed: %s\n", libusb_error_name(t));
      return -1;
    }
    /* The STLink doesn't seem to evaluate the sequence number */
    handle->sg_transfer_idx++;
  }

  return res;
}