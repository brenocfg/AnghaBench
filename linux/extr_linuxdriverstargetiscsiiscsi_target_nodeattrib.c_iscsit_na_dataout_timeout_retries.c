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
typedef  scalar_t__ u32 ;
struct iscsi_node_attrib {scalar_t__ dataout_timeout_retries; } ;
struct iscsi_node_acl {struct iscsi_node_attrib node_attrib; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NA_DATAOUT_TIMEOUT_RETRIES_MAX ; 
 scalar_t__ NA_DATAOUT_TIMEOUT_RETRIES_MIN ; 
 int /*<<< orphan*/  iscsit_na_get_initiatorname (struct iscsi_node_acl*) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,scalar_t__) ; 

int iscsit_na_dataout_timeout_retries(
	struct iscsi_node_acl *acl,
	u32 dataout_timeout_retries)
{
	struct iscsi_node_attrib *a = &acl->node_attrib;

	if (dataout_timeout_retries > NA_DATAOUT_TIMEOUT_RETRIES_MAX) {
		pr_err("Requested DataOut Timeout Retries %u larger"
			" than maximum %u", dataout_timeout_retries,
				NA_DATAOUT_TIMEOUT_RETRIES_MAX);
		return -EINVAL;
	} else if (dataout_timeout_retries < NA_DATAOUT_TIMEOUT_RETRIES_MIN) {
		pr_err("Requested DataOut Timeout Retries %u smaller"
			" than minimum %u", dataout_timeout_retries,
				NA_DATAOUT_TIMEOUT_RETRIES_MIN);
		return -EINVAL;
	}

	a->dataout_timeout_retries = dataout_timeout_retries;
	pr_debug("Set DataOut Timeout Retries to %u for"
		" Initiator Node %s\n", a->dataout_timeout_retries,
		iscsit_na_get_initiatorname(acl));

	return 0;
}