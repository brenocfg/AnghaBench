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

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t LLCP_TLV_MAX ; 
 size_t* kzalloc (int,int /*<<< orphan*/ ) ; 
 size_t* llcp_tlv_length ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t*,size_t) ; 
 int /*<<< orphan*/  pr_debug (char*,size_t) ; 

u8 *nfc_llcp_build_tlv(u8 type, u8 *value, u8 value_length, u8 *tlv_length)
{
	u8 *tlv, length;

	pr_debug("type %d\n", type);

	if (type >= LLCP_TLV_MAX)
		return NULL;

	length = llcp_tlv_length[type];
	if (length == 0 && value_length == 0)
		return NULL;
	else if (length == 0)
		length = value_length;

	*tlv_length = 2 + length;
	tlv = kzalloc(2 + length, GFP_KERNEL);
	if (tlv == NULL)
		return tlv;

	tlv[0] = type;
	tlv[1] = length;
	memcpy(tlv + 2, value, length);

	return tlv;
}