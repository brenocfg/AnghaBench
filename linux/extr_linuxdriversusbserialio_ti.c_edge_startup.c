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
typedef  scalar_t__ u16 ;
struct usb_serial {TYPE_2__* dev; } ;
struct edgeport_serial {scalar_t__ fw_version; int use_heartbeat; struct usb_serial* serial; int /*<<< orphan*/  heartbeat_work; int /*<<< orphan*/  es_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  idProduct; } ;
struct TYPE_4__ {TYPE_1__ descriptor; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ FW_HEARTBEAT_VERSION_CUTOFF ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ION_DEVICE_ID_TI_EDGEPORT_416 ; 
 scalar_t__ ION_DEVICE_ID_TI_EDGEPORT_416B ; 
 int download_fw (struct edgeport_serial*) ; 
 int /*<<< orphan*/  edge_heartbeat_schedule (struct edgeport_serial*) ; 
 int /*<<< orphan*/  edge_heartbeat_work ; 
 int /*<<< orphan*/  kfree (struct edgeport_serial*) ; 
 struct edgeport_serial* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_serial_data (struct usb_serial*,struct edgeport_serial*) ; 

__attribute__((used)) static int edge_startup(struct usb_serial *serial)
{
	struct edgeport_serial *edge_serial;
	int status;
	u16 product_id;

	/* create our private serial structure */
	edge_serial = kzalloc(sizeof(struct edgeport_serial), GFP_KERNEL);
	if (!edge_serial)
		return -ENOMEM;

	mutex_init(&edge_serial->es_lock);
	edge_serial->serial = serial;
	INIT_DELAYED_WORK(&edge_serial->heartbeat_work, edge_heartbeat_work);
	usb_set_serial_data(serial, edge_serial);

	status = download_fw(edge_serial);
	if (status < 0) {
		kfree(edge_serial);
		return status;
	}

	if (status > 0)
		return 1;	/* bind but do not register any ports */

	product_id = le16_to_cpu(
			edge_serial->serial->dev->descriptor.idProduct);

	/* Currently only the EP/416 models require heartbeat support */
	if (edge_serial->fw_version > FW_HEARTBEAT_VERSION_CUTOFF) {
		if (product_id == ION_DEVICE_ID_TI_EDGEPORT_416 ||
			product_id == ION_DEVICE_ID_TI_EDGEPORT_416B) {
			edge_serial->use_heartbeat = true;
		}
	}

	edge_heartbeat_schedule(edge_serial);

	return 0;
}