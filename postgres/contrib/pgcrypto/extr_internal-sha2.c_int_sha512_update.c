#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  pg_sha512_ctx ;
struct TYPE_4__ {scalar_t__ ptr; } ;
struct TYPE_5__ {TYPE_1__ p; } ;
typedef  TYPE_2__ PX_MD ;

/* Variables and functions */
 int /*<<< orphan*/  pg_sha512_update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static void
int_sha512_update(PX_MD *h, const uint8 *data, unsigned dlen)
{
	pg_sha512_ctx *ctx = (pg_sha512_ctx *) h->p.ptr;

	pg_sha512_update(ctx, data, dlen);
}