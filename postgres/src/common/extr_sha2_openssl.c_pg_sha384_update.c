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
typedef  int /*<<< orphan*/  pg_sha384_ctx ;
typedef  int /*<<< orphan*/  SHA512_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA384_Update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

void
pg_sha384_update(pg_sha384_ctx *ctx, const uint8 *data, size_t len)
{
	SHA384_Update((SHA512_CTX *) ctx, data, len);
}