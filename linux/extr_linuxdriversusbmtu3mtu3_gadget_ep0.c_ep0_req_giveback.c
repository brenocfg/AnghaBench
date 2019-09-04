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
struct usb_request {int dummy; } ;
struct mtu3 {int /*<<< orphan*/  ep0; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtu3_req_complete (int /*<<< orphan*/ ,struct usb_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ep0_req_giveback(struct mtu3 *mtu, struct usb_request *req)
{
	mtu3_req_complete(mtu->ep0, req, 0);
}