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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  pg_sha512_ctx ;
typedef  int /*<<< orphan*/  SHA512_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA512_Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
pg_sha512_final(pg_sha512_ctx *ctx, uint8 *dest)
{
	SHA512_Final(dest, (SHA512_CTX *) ctx);
}