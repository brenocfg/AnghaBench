#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  scalar_t__ uint32_t ;
struct msghdr {scalar_t__ msg_controllen; int /*<<< orphan*/  msg_control; } ;
struct TYPE_7__ {int /*<<< orphan*/  has_error; } ;
struct TYPE_8__ {TYPE_1__ err; } ;
typedef  TYPE_2__ ser_context ;

/* Variables and functions */
 int /*<<< orphan*/  accounted_emalloc (scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  do_from_zval_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  from_zval_write_uint32 (int /*<<< orphan*/  const*,char*,TYPE_2__*) ; 

__attribute__((used)) static void from_zval_write_controllen(const zval *elem, char *msghdr_c, ser_context *ctx)
{
	struct msghdr *msghdr = (struct msghdr *)msghdr_c;
	uint32_t len;

	/* controllen should be an unsigned with at least 32-bit. Let's assume
	 * this least common denominator
	 */
	from_zval_write_uint32(elem, (char*)&len, ctx);
	if (!ctx->err.has_error && len == 0) {
		do_from_zval_err(ctx, "controllen cannot be 0");
		return;
	}
	msghdr->msg_control = accounted_emalloc(len, ctx);
	msghdr->msg_controllen = len;
}