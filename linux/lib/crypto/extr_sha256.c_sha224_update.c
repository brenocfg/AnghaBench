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
 int sha256_update (struct sha256_state*,int /*<<< orphan*/  const*,unsigned int) ; 

int sha224_update(struct sha256_state *sctx, const u8 *data, unsigned int len)
{
	return sha256_update(sctx, data, len);
}