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
struct canfd_frame {int /*<<< orphan*/  data; int /*<<< orphan*/  len; int /*<<< orphan*/  flags; int /*<<< orphan*/  can_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CANFD_MAX_DLEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void canfdframecpy(struct canfd_frame *dst, struct canfd_frame *src)
{
	/* Copy the struct members separately to ensure that no uninitialized
	 * data are copied in the 2 bytes hole of the struct. This is needed
	 * to make easy compares of the data in the struct cf_mod.
	 */

	dst->can_id = src->can_id;
	dst->flags = src->flags;
	dst->len = src->len;
	memcpy(dst->data, src->data, CANFD_MAX_DLEN);
}