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
typedef  scalar_t__ u8 ;
struct mlme_set_request_pset {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  pib_attribute_value; scalar_t__ pib_attribute_length; scalar_t__ pib_attribute_index; scalar_t__ pib_attribute; } ;
struct TYPE_4__ {scalar_t__ status; TYPE_1__ set_req; } ;
struct mac_message {scalar_t__ command_id; int length; TYPE_2__ pdata; } ;

/* Variables and functions */
 scalar_t__ MAC_INVALID_PARAMETER ; 
 scalar_t__ MAC_SYSTEM_ERROR ; 
 int MAX_ATTRIBUTE_SIZE ; 
 scalar_t__ PHY_CURRENT_CHANNEL ; 
 scalar_t__ PHY_TRANSMIT_POWER ; 
 scalar_t__ SPI_MLME_SET_CONFIRM ; 
 scalar_t__ SPI_MLME_SET_REQUEST ; 
 scalar_t__ cascoda_api_downstream (scalar_t__*,int,scalar_t__*,void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,scalar_t__) ; 
 scalar_t__ tdme_channelinit (scalar_t__,void*) ; 
 scalar_t__ tdme_checkpibattribute (scalar_t__,scalar_t__,void const*) ; 
 scalar_t__ tdme_settxpower (scalar_t__,void*) ; 

__attribute__((used)) static u8 mlme_set_request_sync(
	u8            pib_attribute,
	u8            pib_attribute_index,
	u8            pib_attribute_length,
	const void   *pib_attribute_value,
	void         *device_ref
)
{
	u8 status;
	struct mac_message command, response;

	/* pre-check the validity of pib_attribute values that are not checked
	 * in MAC
	 */
	if (tdme_checkpibattribute(
		pib_attribute, pib_attribute_length, pib_attribute_value)) {
		return MAC_INVALID_PARAMETER;
	}

	if (pib_attribute == PHY_CURRENT_CHANNEL) {
		status = tdme_channelinit(
			*((u8 *)pib_attribute_value),
			device_ref
		);
		if (status)
			return status;
	}

	if (pib_attribute == PHY_TRANSMIT_POWER) {
		return tdme_settxpower(
			*((u8 *)pib_attribute_value),
			device_ref
		);
	}

	command.command_id = SPI_MLME_SET_REQUEST;
	command.length = sizeof(struct mlme_set_request_pset) -
		MAX_ATTRIBUTE_SIZE + pib_attribute_length;
	command.pdata.set_req.pib_attribute = pib_attribute;
	command.pdata.set_req.pib_attribute_index = pib_attribute_index;
	command.pdata.set_req.pib_attribute_length = pib_attribute_length;
	memcpy(
		command.pdata.set_req.pib_attribute_value,
		pib_attribute_value,
		pib_attribute_length
	);

	if (cascoda_api_downstream(
		&command.command_id,
		command.length + 2,
		&response.command_id,
		device_ref)) {
		return MAC_SYSTEM_ERROR;
	}

	if (response.command_id != SPI_MLME_SET_CONFIRM)
		return MAC_SYSTEM_ERROR;

	return response.pdata.status;
}