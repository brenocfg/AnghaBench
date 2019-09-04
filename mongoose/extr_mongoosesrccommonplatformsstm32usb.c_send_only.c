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
struct stlink_libusb {int dummy; } ;

/* Variables and functions */
 scalar_t__ send_recv (struct stlink_libusb*,int,unsigned char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int send_only(struct stlink_libusb *handle, int terminate,
                            unsigned char *txbuf, size_t txsize) {
  return (int) send_recv(handle, terminate, txbuf, txsize, NULL, 0);
}