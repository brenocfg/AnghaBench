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
typedef  int /*<<< orphan*/  u8 ;
struct ufs_hba {int dummy; } ;
typedef  enum query_opcode { ____Placeholder_query_opcode } query_opcode ;
typedef  enum desc_idn { ____Placeholder_desc_idn } desc_idn ;

/* Variables and functions */
 int EINVAL ; 
 int QUERY_REQ_RETRIES ; 
 int __ufshcd_query_descriptor (struct ufs_hba*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

int ufshcd_query_descriptor_retry(struct ufs_hba *hba,
				  enum query_opcode opcode,
				  enum desc_idn idn, u8 index,
				  u8 selector,
				  u8 *desc_buf, int *buf_len)
{
	int err;
	int retries;

	for (retries = QUERY_REQ_RETRIES; retries > 0; retries--) {
		err = __ufshcd_query_descriptor(hba, opcode, idn, index,
						selector, desc_buf, buf_len);
		if (!err || err == -EINVAL)
			break;
	}

	return err;
}