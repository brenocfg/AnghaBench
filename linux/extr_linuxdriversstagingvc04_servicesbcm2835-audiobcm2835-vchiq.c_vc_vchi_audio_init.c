#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bcm2835_audio_instance {int /*<<< orphan*/  vchi_handle; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  VCHI_INSTANCE_T ;
typedef  int /*<<< orphan*/  VCHI_CONNECTION_T ;
struct TYPE_3__ {int want_unaligned_bulk_rx; int want_unaligned_bulk_tx; int /*<<< orphan*/  want_crc; struct bcm2835_audio_instance* callback_param; int /*<<< orphan*/  callback; int /*<<< orphan*/  tx_fifo_size; int /*<<< orphan*/  rx_fifo_size; int /*<<< orphan*/ * connection; int /*<<< orphan*/  service_id; int /*<<< orphan*/  version; } ;
typedef  TYPE_1__ SERVICE_CREATION_T ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  VCHI_VERSION_EX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VC_AUDIOSERV_MIN_VER ; 
 int /*<<< orphan*/  VC_AUDIOSERV_VER ; 
 int /*<<< orphan*/  VC_AUDIO_SERVER_NAME ; 
 int /*<<< orphan*/  audio_vchi_callback ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int vchi_service_open (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchi_service_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vc_vchi_audio_init(VCHI_INSTANCE_T vchi_instance,
		   VCHI_CONNECTION_T *vchi_connection,
		   struct bcm2835_audio_instance *instance)
{
	SERVICE_CREATION_T params = {
		.version		= VCHI_VERSION_EX(VC_AUDIOSERV_VER, VC_AUDIOSERV_MIN_VER),
		.service_id		= VC_AUDIO_SERVER_NAME,
		.connection		= vchi_connection,
		.rx_fifo_size		= 0,
		.tx_fifo_size		= 0,
		.callback		= audio_vchi_callback,
		.callback_param		= instance,
		.want_unaligned_bulk_rx = 1, //TODO: remove VCOS_FALSE
		.want_unaligned_bulk_tx = 1, //TODO: remove VCOS_FALSE
		.want_crc		= 0
	};
	int status;

	/* Open the VCHI service connections */
	status = vchi_service_open(vchi_instance, &params,
				   &instance->vchi_handle);

	if (status) {
		dev_err(instance->dev,
			"failed to open VCHI service connection (status=%d)\n",
			status);
		return -EPERM;
	}

	/* Finished with the service for now */
	vchi_service_release(instance->vchi_handle);

	return 0;
}