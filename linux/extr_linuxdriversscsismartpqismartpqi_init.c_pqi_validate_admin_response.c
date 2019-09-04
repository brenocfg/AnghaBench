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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {scalar_t__ iu_type; int /*<<< orphan*/  iu_length; } ;
struct pqi_general_admin_response {scalar_t__ function_code; scalar_t__ status; TYPE_1__ header; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PQI_GENERAL_ADMIN_IU_LENGTH ; 
 scalar_t__ PQI_GENERAL_ADMIN_STATUS_SUCCESS ; 
 scalar_t__ PQI_RESPONSE_IU_GENERAL_ADMIN ; 
 scalar_t__ get_unaligned_le16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pqi_validate_admin_response(
	struct pqi_general_admin_response *response, u8 expected_function_code)
{
	if (response->header.iu_type != PQI_RESPONSE_IU_GENERAL_ADMIN)
		return -EINVAL;

	if (get_unaligned_le16(&response->header.iu_length) !=
		PQI_GENERAL_ADMIN_IU_LENGTH)
		return -EINVAL;

	if (response->function_code != expected_function_code)
		return -EINVAL;

	if (response->status != PQI_GENERAL_ADMIN_STATUS_SUCCESS)
		return -EINVAL;

	return 0;
}