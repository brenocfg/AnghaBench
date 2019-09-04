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
struct sisusb_usb_data {int /*<<< orphan*/ * ibuf; int /*<<< orphan*/ ** obuf; } ;

/* Variables and functions */
 int NUMOBUFS ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sisusb_free_buffers(struct sisusb_usb_data *sisusb)
{
	int i;

	for (i = 0; i < NUMOBUFS; i++) {
		kfree(sisusb->obuf[i]);
		sisusb->obuf[i] = NULL;
	}
	kfree(sisusb->ibuf);
	sisusb->ibuf = NULL;
}