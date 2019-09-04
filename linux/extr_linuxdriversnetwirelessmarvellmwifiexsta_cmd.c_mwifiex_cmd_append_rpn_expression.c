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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mwifiex_private {int dummy; } ;
struct mwifiex_mef_filter {int filt_type; int* byte_seq; int filt_action; scalar_t__ offset; scalar_t__ repeat; } ;
struct mwifiex_mef_entry {struct mwifiex_mef_filter* filter; } ;

/* Variables and functions */
 size_t MWIFIEX_MEF_MAX_BYTESEQ ; 
 int MWIFIEX_MEF_MAX_FILTERS ; 
 int STACK_NBYTES ; 
 int TYPE_BYTESEQ ; 
 int TYPE_DNUM ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
mwifiex_cmd_append_rpn_expression(struct mwifiex_private *priv,
				  struct mwifiex_mef_entry *mef_entry,
				  u8 **buffer)
{
	struct mwifiex_mef_filter *filter = mef_entry->filter;
	int i, byte_len;
	u8 *stack_ptr = *buffer;

	for (i = 0; i < MWIFIEX_MEF_MAX_FILTERS; i++) {
		filter = &mef_entry->filter[i];
		if (!filter->filt_type)
			break;
		put_unaligned_le32((u32)filter->repeat, stack_ptr);
		stack_ptr += 4;
		*stack_ptr = TYPE_DNUM;
		stack_ptr += 1;

		byte_len = filter->byte_seq[MWIFIEX_MEF_MAX_BYTESEQ];
		memcpy(stack_ptr, filter->byte_seq, byte_len);
		stack_ptr += byte_len;
		*stack_ptr = byte_len;
		stack_ptr += 1;
		*stack_ptr = TYPE_BYTESEQ;
		stack_ptr += 1;
		put_unaligned_le32((u32)filter->offset, stack_ptr);
		stack_ptr += 4;
		*stack_ptr = TYPE_DNUM;
		stack_ptr += 1;

		*stack_ptr = filter->filt_type;
		stack_ptr += 1;

		if (filter->filt_action) {
			*stack_ptr = filter->filt_action;
			stack_ptr += 1;
		}

		if (stack_ptr - *buffer > STACK_NBYTES)
			return -1;
	}

	*buffer = stack_ptr;
	return 0;
}