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
struct sha256_state {int dummy; } ;

/* Variables and functions */
 int __sha256_final (struct sha256_state*,int /*<<< orphan*/ *,int) ; 

int sha256_final(struct sha256_state *sctx, u8 *out)
{
	return __sha256_final(sctx, out, 8);
}