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
typedef  scalar_t__ u64 ;
struct machine {int dummy; } ;
struct eh_frame_hdr {int /*<<< orphan*/  fde_count_enc; int /*<<< orphan*/  eh_frame_ptr_enc; int /*<<< orphan*/  data; int /*<<< orphan*/  enc; } ;
struct dso {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  hdr ;

/* Variables and functions */
 int EINVAL ; 
 int dso__data_read_offset (struct dso*,struct machine*,scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ dw_read_encoded_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unwind_spec_ehframe(struct dso *dso, struct machine *machine,
			       u64 offset, u64 *table_data, u64 *segbase,
			       u64 *fde_count)
{
	struct eh_frame_hdr hdr;
	u8 *enc = (u8 *) &hdr.enc;
	u8 *end = (u8 *) &hdr.data;
	ssize_t r;

	r = dso__data_read_offset(dso, machine, offset,
				  (u8 *) &hdr, sizeof(hdr));
	if (r != sizeof(hdr))
		return -EINVAL;

	/* We dont need eh_frame_ptr, just skip it. */
	dw_read_encoded_value(enc, end, hdr.eh_frame_ptr_enc);

	*fde_count  = dw_read_encoded_value(enc, end, hdr.fde_count_enc);
	*segbase    = offset;
	*table_data = (enc - (u8 *) &hdr) + offset;
	return 0;
}