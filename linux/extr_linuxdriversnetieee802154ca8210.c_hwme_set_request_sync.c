#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
struct TYPE_4__ {void* status; } ;
struct TYPE_6__ {int /*<<< orphan*/  hw_attribute_value; void* hw_attribute_length; void* hw_attribute; } ;
struct TYPE_5__ {TYPE_1__ hwme_set_cnf; TYPE_3__ hwme_set_req; } ;
struct mac_message {scalar_t__ command_id; TYPE_2__ pdata; scalar_t__ length; } ;

/* Variables and functions */
 void* MAC_SYSTEM_ERROR ; 
 scalar_t__ SPI_HWME_SET_CONFIRM ; 
 scalar_t__ SPI_HWME_SET_REQUEST ; 
 scalar_t__ cascoda_api_downstream (scalar_t__*,scalar_t__,scalar_t__*,void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void**,void*) ; 

__attribute__((used)) static u8 hwme_set_request_sync(
	u8           hw_attribute,
	u8           hw_attribute_length,
	u8          *hw_attribute_value,
	void        *device_ref
)
{
	struct mac_message command, response;

	command.command_id = SPI_HWME_SET_REQUEST;
	command.length = 2 + hw_attribute_length;
	command.pdata.hwme_set_req.hw_attribute = hw_attribute;
	command.pdata.hwme_set_req.hw_attribute_length = hw_attribute_length;
	memcpy(
		command.pdata.hwme_set_req.hw_attribute_value,
		hw_attribute_value,
		hw_attribute_length
	);

	if (cascoda_api_downstream(
		&command.command_id,
		command.length + 2,
		&response.command_id,
		device_ref)) {
		return MAC_SYSTEM_ERROR;
	}

	if (response.command_id != SPI_HWME_SET_CONFIRM)
		return MAC_SYSTEM_ERROR;

	return response.pdata.hwme_set_cnf.status;
}