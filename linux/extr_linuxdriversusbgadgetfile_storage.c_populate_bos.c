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
struct fsg_dev {int dummy; } ;

/* Variables and functions */
 int USB_DT_BOS_SIZE ; 
 int USB_DT_USB_EXT_CAP_SIZE ; 
 int USB_DT_USB_SS_CAP_SIZE ; 
 int /*<<< orphan*/  fsg_bos_desc ; 
 int /*<<< orphan*/  fsg_ext_cap_desc ; 
 int /*<<< orphan*/  fsg_ss_cap_desc ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int populate_bos(struct fsg_dev *fsg, u8 *buf)
{
	memcpy(buf, &fsg_bos_desc, USB_DT_BOS_SIZE);
	buf += USB_DT_BOS_SIZE;

	memcpy(buf, &fsg_ext_cap_desc, USB_DT_USB_EXT_CAP_SIZE);
	buf += USB_DT_USB_EXT_CAP_SIZE;

	memcpy(buf, &fsg_ss_cap_desc, USB_DT_USB_SS_CAP_SIZE);

	return USB_DT_BOS_SIZE + USB_DT_USB_SS_CAP_SIZE
		+ USB_DT_USB_EXT_CAP_SIZE;
}