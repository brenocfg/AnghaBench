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
struct acm {TYPE_1__* data; int /*<<< orphan*/  read_urbs_free; int /*<<< orphan*/ * read_urbs; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPERM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int,int /*<<< orphan*/ *) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acm_submit_read_urb(struct acm *acm, int index, gfp_t mem_flags)
{
	int res;

	if (!test_and_clear_bit(index, &acm->read_urbs_free))
		return 0;

	res = usb_submit_urb(acm->read_urbs[index], mem_flags);
	if (res) {
		if (res != -EPERM && res != -ENODEV) {
			dev_err(&acm->data->dev,
				"urb %d failed submission with %d\n",
				index, res);
		}
		set_bit(index, &acm->read_urbs_free);
		return res;
	} else {
		dev_vdbg(&acm->data->dev, "submitted urb %d\n", index);
	}

	return 0;
}