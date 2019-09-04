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
typedef  scalar_t__ u32 ;
struct esas2r_sg_context {scalar_t__ cur_offset; scalar_t__ adapter; } ;
struct esas2r_adapter {scalar_t__ ppvda_buffer; scalar_t__ vda_buffer; } ;

/* Variables and functions */
 scalar_t__ VDA_MAX_BUFFER_SIZE ; 

__attribute__((used)) static u32 get_physaddr_vda(struct esas2r_sg_context *sgc, u64 *addr)
{
	struct esas2r_adapter *a = (struct esas2r_adapter *)sgc->adapter;
	int offset = (u8 *)sgc->cur_offset - (u8 *)a->vda_buffer;

	(*addr) = a->ppvda_buffer + offset;
	return VDA_MAX_BUFFER_SIZE - offset;
}