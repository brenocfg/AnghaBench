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
struct dlm_rcom {void* rc_seq_reply; void* rc_seq; void* rc_id; void* rc_result; void* rc_type; int /*<<< orphan*/  rc_header; } ;

/* Variables and functions */
 void* cpu_to_le32 (void*) ; 
 void* cpu_to_le64 (void*) ; 
 int /*<<< orphan*/  header_out (int /*<<< orphan*/ *) ; 

void dlm_rcom_out(struct dlm_rcom *rc)
{
	header_out(&rc->rc_header);

	rc->rc_type		= cpu_to_le32(rc->rc_type);
	rc->rc_result		= cpu_to_le32(rc->rc_result);
	rc->rc_id		= cpu_to_le64(rc->rc_id);
	rc->rc_seq		= cpu_to_le64(rc->rc_seq);
	rc->rc_seq_reply	= cpu_to_le64(rc->rc_seq_reply);
}