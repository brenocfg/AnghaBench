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
typedef  int /*<<< orphan*/  u32 ;
struct wcn36xx_hal_cfg {int len; scalar_t__ reserve; scalar_t__ pad_bytes; int /*<<< orphan*/  id; } ;
struct wcn36xx {scalar_t__ hal_buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 size_t WCN36XX_HAL_BUF_SIZE ; 
 int /*<<< orphan*/  wcn36xx_err (char*) ; 

__attribute__((used)) static int put_cfg_tlv_u32(struct wcn36xx *wcn, size_t *len, u32 id, u32 value)
{
	struct wcn36xx_hal_cfg *entry;
	u32 *val;

	if (*len + sizeof(*entry) + sizeof(u32) >= WCN36XX_HAL_BUF_SIZE) {
		wcn36xx_err("Not enough room for TLV entry\n");
		return -ENOMEM;
	}

	entry = (struct wcn36xx_hal_cfg *) (wcn->hal_buf + *len);
	entry->id = id;
	entry->len = sizeof(u32);
	entry->pad_bytes = 0;
	entry->reserve = 0;

	val = (u32 *) (entry + 1);
	*val = value;

	*len += sizeof(*entry) + sizeof(u32);

	return 0;
}