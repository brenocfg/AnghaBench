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
struct nd_cmd_get_config_data_hdr {unsigned int in_offset; int in_length; int /*<<< orphan*/  out_buf; scalar_t__ status; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int LABEL_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,unsigned int) ; 
 unsigned int min (int,unsigned int) ; 

__attribute__((used)) static int nfit_test_cmd_get_config_data(struct nd_cmd_get_config_data_hdr
		*nd_cmd, unsigned int buf_len, void *label)
{
	unsigned int len, offset = nd_cmd->in_offset;
	int rc;

	if (buf_len < sizeof(*nd_cmd))
		return -EINVAL;
	if (offset >= LABEL_SIZE)
		return -EINVAL;
	if (nd_cmd->in_length + sizeof(*nd_cmd) > buf_len)
		return -EINVAL;

	nd_cmd->status = 0;
	len = min(nd_cmd->in_length, LABEL_SIZE - offset);
	memcpy(nd_cmd->out_buf, label + offset, len);
	rc = buf_len - sizeof(*nd_cmd) - len;

	return rc;
}