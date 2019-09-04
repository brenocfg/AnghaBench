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
typedef  scalar_t__ u8 ;
struct gb_fw_mgmt_load_and_validate_fw_request {char* firmware_tag; int request_id; scalar_t__ load_method; } ;
struct fw_mgmt {int intf_fw_request_id; int intf_fw_loaded; int /*<<< orphan*/  parent; int /*<<< orphan*/  id_map; int /*<<< orphan*/  connection; } ;
typedef  int /*<<< orphan*/  request ;

/* Variables and functions */
 int EINVAL ; 
 int GB_FIRMWARE_TAG_MAX_SIZE ; 
 scalar_t__ GB_FW_LOAD_METHOD_INTERNAL ; 
 scalar_t__ GB_FW_LOAD_METHOD_UNIPRO ; 
 int /*<<< orphan*/  GB_FW_MGMT_TYPE_LOAD_AND_VALIDATE_FW ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gb_fw_mgmt_load_and_validate_fw_request*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static int fw_mgmt_load_and_validate_operation(struct fw_mgmt *fw_mgmt,
					       u8 load_method, const char *tag)
{
	struct gb_fw_mgmt_load_and_validate_fw_request request;
	int ret;

	if (load_method != GB_FW_LOAD_METHOD_UNIPRO &&
	    load_method != GB_FW_LOAD_METHOD_INTERNAL) {
		dev_err(fw_mgmt->parent,
			"invalid load-method (%d)\n", load_method);
		return -EINVAL;
	}

	request.load_method = load_method;
	strncpy(request.firmware_tag, tag, GB_FIRMWARE_TAG_MAX_SIZE);

	/*
	 * The firmware-tag should be NULL terminated, otherwise throw error and
	 * fail.
	 */
	if (request.firmware_tag[GB_FIRMWARE_TAG_MAX_SIZE - 1] != '\0') {
		dev_err(fw_mgmt->parent, "load-and-validate: firmware-tag is not NULL terminated\n");
		return -EINVAL;
	}

	/* Allocate ids from 1 to 255 (u8-max), 0 is an invalid id */
	ret = ida_simple_get(&fw_mgmt->id_map, 1, 256, GFP_KERNEL);
	if (ret < 0) {
		dev_err(fw_mgmt->parent, "failed to allocate request id (%d)\n",
			ret);
		return ret;
	}

	fw_mgmt->intf_fw_request_id = ret;
	fw_mgmt->intf_fw_loaded = false;
	request.request_id = ret;

	ret = gb_operation_sync(fw_mgmt->connection,
				GB_FW_MGMT_TYPE_LOAD_AND_VALIDATE_FW, &request,
				sizeof(request), NULL, 0);
	if (ret) {
		ida_simple_remove(&fw_mgmt->id_map,
				  fw_mgmt->intf_fw_request_id);
		fw_mgmt->intf_fw_request_id = 0;
		dev_err(fw_mgmt->parent,
			"load and validate firmware request failed (%d)\n",
			ret);
		return ret;
	}

	return 0;
}