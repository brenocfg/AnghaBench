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
typedef  int uint32_t ;
struct amt_host_if_resp_header {int dummy; } ;
struct TYPE_2__ {scalar_t__ major; scalar_t__ minor; } ;
struct amt_host_if_msg_header {int length; int command; scalar_t__ _reserved; TYPE_1__ version; } ;

/* Variables and functions */
 scalar_t__ AMT_MAJOR_VERSION ; 
 scalar_t__ AMT_MINOR_VERSION ; 
 int AMT_STATUS_INTERNAL_ERROR ; 
 int AMT_STATUS_SUCCESS ; 

__attribute__((used)) static uint32_t amt_verify_response_header(uint32_t command,
				const struct amt_host_if_msg_header *resp_hdr,
				uint32_t response_size)
{
	if (response_size < sizeof(struct amt_host_if_resp_header)) {
		return AMT_STATUS_INTERNAL_ERROR;
	} else if (response_size != (resp_hdr->length +
				sizeof(struct amt_host_if_msg_header))) {
		return AMT_STATUS_INTERNAL_ERROR;
	} else if (resp_hdr->command != command) {
		return AMT_STATUS_INTERNAL_ERROR;
	} else if (resp_hdr->_reserved != 0) {
		return AMT_STATUS_INTERNAL_ERROR;
	} else if (resp_hdr->version.major != AMT_MAJOR_VERSION ||
		   resp_hdr->version.minor < AMT_MINOR_VERSION) {
		return AMT_STATUS_INTERNAL_ERROR;
	}
	return AMT_STATUS_SUCCESS;
}