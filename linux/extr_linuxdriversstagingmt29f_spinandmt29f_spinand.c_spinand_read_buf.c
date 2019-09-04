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
struct spinand_state {scalar_t__ buf_ptr; scalar_t__ buf; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 struct spinand_state* mtd_to_state (struct mtd_info*) ; 

__attribute__((used)) static void spinand_read_buf(struct mtd_info *mtd, u8 *buf, int len)
{
	struct spinand_state *state = mtd_to_state(mtd);

	memcpy(buf, state->buf + state->buf_ptr, len);
	state->buf_ptr += len;
}