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
struct TYPE_4__ {scalar_t__ length; int buffer_len; int code; scalar_t__* buffer; int /*<<< orphan*/  mode; } ;
union fjes_device_command_res {TYPE_2__ start_trace; } ;
union fjes_device_command_req {TYPE_2__ start_trace; } ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int trace_size; union fjes_device_command_res* trace; int /*<<< orphan*/  res_buf_size; int /*<<< orphan*/  req_buf_size; union fjes_device_command_res* res_buf; union fjes_device_command_res* req_buf; } ;
struct fjes_hw {TYPE_1__ hw_info; int /*<<< orphan*/  debug_mode; } ;
typedef  enum fjes_dev_command_response_e { ____Placeholder_fjes_dev_command_response_e } fjes_dev_command_response_e ;
typedef  scalar_t__ __le64 ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMSG ; 
 int EPERM ; 
#define  FJES_CMD_REQ_RES_CODE_NORMAL 132 
 int /*<<< orphan*/  FJES_CMD_REQ_START_DEBUG ; 
#define  FJES_CMD_STATUS_ERROR_PARAM 131 
#define  FJES_CMD_STATUS_ERROR_STATUS 130 
 int FJES_CMD_STATUS_NORMAL ; 
#define  FJES_CMD_STATUS_TIMEOUT 129 
#define  FJES_CMD_STATUS_UNKNOWN 128 
 int /*<<< orphan*/  FJES_DEBUG_BUFFER_SIZE ; 
 int FJES_DEBUG_PAGE_SIZE ; 
 scalar_t__ FJES_DEV_COMMAND_START_DBG_REQ_LEN (int) ; 
 scalar_t__ FJES_DEV_COMMAND_START_DBG_RES_LEN ; 
 int fjes_hw_issue_request_command (struct fjes_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (union fjes_device_command_res*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ offset_in_page (void*) ; 
 scalar_t__ page_to_phys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_fjes_hw_start_debug (union fjes_device_command_res*) ; 
 int /*<<< orphan*/  trace_fjes_hw_start_debug_err (char*) ; 
 int /*<<< orphan*/  trace_fjes_hw_start_debug_req (union fjes_device_command_res*) ; 
 int /*<<< orphan*/  vmalloc_to_page (void*) ; 

int fjes_hw_start_debug(struct fjes_hw *hw)
{
	union fjes_device_command_req *req_buf = hw->hw_info.req_buf;
	union fjes_device_command_res *res_buf = hw->hw_info.res_buf;
	enum fjes_dev_command_response_e ret;
	int page_count;
	int result = 0;
	void *addr;
	int i;

	if (!hw->hw_info.trace)
		return -EPERM;
	memset(hw->hw_info.trace, 0, FJES_DEBUG_BUFFER_SIZE);

	memset(req_buf, 0, hw->hw_info.req_buf_size);
	memset(res_buf, 0, hw->hw_info.res_buf_size);

	req_buf->start_trace.length =
		FJES_DEV_COMMAND_START_DBG_REQ_LEN(hw->hw_info.trace_size);
	req_buf->start_trace.mode = hw->debug_mode;
	req_buf->start_trace.buffer_len = hw->hw_info.trace_size;
	page_count = hw->hw_info.trace_size / FJES_DEBUG_PAGE_SIZE;
	for (i = 0; i < page_count; i++) {
		addr = ((u8 *)hw->hw_info.trace) + i * FJES_DEBUG_PAGE_SIZE;
		req_buf->start_trace.buffer[i] =
			(__le64)(page_to_phys(vmalloc_to_page(addr)) +
			offset_in_page(addr));
	}

	res_buf->start_trace.length = 0;
	res_buf->start_trace.code = 0;

	trace_fjes_hw_start_debug_req(req_buf);
	ret = fjes_hw_issue_request_command(hw, FJES_CMD_REQ_START_DEBUG);
	trace_fjes_hw_start_debug(res_buf);

	if (res_buf->start_trace.length !=
		FJES_DEV_COMMAND_START_DBG_RES_LEN) {
		result = -ENOMSG;
		trace_fjes_hw_start_debug_err("Invalid res_buf");
	} else if (ret == FJES_CMD_STATUS_NORMAL) {
		switch (res_buf->start_trace.code) {
		case FJES_CMD_REQ_RES_CODE_NORMAL:
			result = 0;
			break;
		default:
			result = -EPERM;
			break;
		}
	} else {
		switch (ret) {
		case FJES_CMD_STATUS_UNKNOWN:
			result = -EPERM;
			break;
		case FJES_CMD_STATUS_TIMEOUT:
			trace_fjes_hw_start_debug_err("Busy Timeout");
			result = -EBUSY;
			break;
		case FJES_CMD_STATUS_ERROR_PARAM:
		case FJES_CMD_STATUS_ERROR_STATUS:
		default:
			result = -EPERM;
			break;
		}
	}

	return result;
}