#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  md; } ;
typedef  TYPE_1__ PX_HMAC ;

/* Variables and functions */
 int px_md_block_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned
hmac_block_size(PX_HMAC *h)
{
	return px_md_block_size(h->md);
}