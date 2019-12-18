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

/* Variables and functions */
 int /*<<< orphan*/  pg_sha256_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_sha256_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_sha256_update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

void
scram_H(const uint8 *input, int len, uint8 *result)
{
	pg_sha256_ctx ctx;

	pg_sha256_init(&ctx);
	pg_sha256_update(&ctx, input, len);
	pg_sha256_final(&ctx, result);
}