#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct raw_data {int /*<<< orphan*/  entry; int /*<<< orphan*/ * data; scalar_t__ len; } ;
struct gb_raw {scalar_t__ list_data; int /*<<< orphan*/  list_lock; int /*<<< orphan*/  list; TYPE_2__* connection; } ;
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* bundle; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MAX_DATA_SIZE ; 
 scalar_t__ MAX_PACKET_SIZE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct raw_data* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int receive_data(struct gb_raw *raw, u32 len, u8 *data)
{
	struct raw_data *raw_data;
	struct device *dev = &raw->connection->bundle->dev;
	int retval = 0;

	if (len > MAX_PACKET_SIZE) {
		dev_err(dev, "Too big of a data packet, rejected\n");
		return -EINVAL;
	}

	mutex_lock(&raw->list_lock);
	if ((raw->list_data + len) > MAX_DATA_SIZE) {
		dev_err(dev, "Too much data in receive buffer, now dropping packets\n");
		retval = -EINVAL;
		goto exit;
	}

	raw_data = kmalloc(sizeof(*raw_data) + len, GFP_KERNEL);
	if (!raw_data) {
		retval = -ENOMEM;
		goto exit;
	}

	raw->list_data += len;
	raw_data->len = len;
	memcpy(&raw_data->data[0], data, len);

	list_add_tail(&raw_data->entry, &raw->list);
exit:
	mutex_unlock(&raw->list_lock);
	return retval;
}