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
struct ar5523_rx_data {int /*<<< orphan*/  list; int /*<<< orphan*/  urb; struct ar5523* ar; } ;
struct ar5523 {int /*<<< orphan*/  rx_data_free_cnt; int /*<<< orphan*/  rx_data_free; struct ar5523_rx_data* rx_data; } ;

/* Variables and functions */
 int AR5523_RX_DATA_COUNT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ar5523_free_rx_bufs (struct ar5523*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ar5523_alloc_rx_bufs(struct ar5523 *ar)
{
	int i;

	for (i = 0; i < AR5523_RX_DATA_COUNT; i++) {
		struct ar5523_rx_data *data = &ar->rx_data[i];

		data->ar = ar;
		data->urb = usb_alloc_urb(0, GFP_KERNEL);
		if (!data->urb)
			goto err;
		list_add_tail(&data->list, &ar->rx_data_free);
		atomic_inc(&ar->rx_data_free_cnt);
	}
	return 0;

err:
	ar5523_free_rx_bufs(ar);
	return -ENOMEM;
}