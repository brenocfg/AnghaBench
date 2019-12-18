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
struct TYPE_4__ {scalar_t__ ptr; } ;
struct TYPE_5__ {TYPE_1__ p; } ;
typedef  int /*<<< orphan*/  SHA1_CTX ;
typedef  TYPE_2__ PX_MD ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
int_sha1_finish(PX_MD *h, uint8 *dst)
{
	SHA1_CTX   *ctx = (SHA1_CTX *) h->p.ptr;

	SHA1Final(dst, ctx);
}