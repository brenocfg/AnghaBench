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
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,int) ; 
 struct spinand_state* mtd_to_state (struct mtd_info*) ; 

__attribute__((used)) static void spinand_write_buf(struct mtd_info *mtd, const u8 *buf, int len)
{
	struct spinand_state *state = mtd_to_state(mtd);

	memcpy(state->buf + state->buf_ptr, buf, len);
	state->buf_ptr += len;
}