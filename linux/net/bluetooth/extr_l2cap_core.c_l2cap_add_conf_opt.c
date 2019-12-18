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
typedef  size_t u8 ;
struct l2cap_conf_opt {size_t type; size_t len; scalar_t__ val; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,size_t,size_t,unsigned long) ; 
 size_t L2CAP_CONF_OPT_SIZE ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,size_t) ; 
 int /*<<< orphan*/  put_unaligned_le16 (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  put_unaligned_le32 (unsigned long,scalar_t__) ; 

__attribute__((used)) static void l2cap_add_conf_opt(void **ptr, u8 type, u8 len, unsigned long val, size_t size)
{
	struct l2cap_conf_opt *opt = *ptr;

	BT_DBG("type 0x%2.2x len %u val 0x%lx", type, len, val);

	if (size < L2CAP_CONF_OPT_SIZE + len)
		return;

	opt->type = type;
	opt->len  = len;

	switch (len) {
	case 1:
		*((u8 *) opt->val)  = val;
		break;

	case 2:
		put_unaligned_le16(val, opt->val);
		break;

	case 4:
		put_unaligned_le32(val, opt->val);
		break;

	default:
		memcpy(opt->val, (void *) val, len);
		break;
	}

	*ptr += L2CAP_CONF_OPT_SIZE + len;
}