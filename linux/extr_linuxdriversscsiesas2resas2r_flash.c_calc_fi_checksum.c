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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct esas2r_flash_img {int length; } ;
struct esas2r_flash_context {int fi_hdr_len; struct esas2r_flash_img* fi; } ;

/* Variables and functions */
 scalar_t__ le16_to_cpu (scalar_t__) ; 

__attribute__((used)) static u16 calc_fi_checksum(struct esas2r_flash_context *fc)
{
	struct esas2r_flash_img *fi = fc->fi;
	u16 cksum;
	u32 len;
	u16 *pw;

	for (len = (fi->length - fc->fi_hdr_len) / 2,
	     pw = (u16 *)((u8 *)fi + fc->fi_hdr_len),
	     cksum = 0;
	     len;
	     len--, pw++)
		cksum = cksum + le16_to_cpu(*pw);

	return cksum;
}