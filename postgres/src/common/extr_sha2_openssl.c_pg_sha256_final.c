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
typedef  int /*<<< orphan*/  pg_sha256_ctx ;
typedef  int /*<<< orphan*/  SHA256_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA256_Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
pg_sha256_final(pg_sha256_ctx *ctx, uint8 *dest)
{
	SHA256_Final(dest, (SHA256_CTX *) ctx);
}