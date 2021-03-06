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
typedef  int /*<<< orphan*/  pg_sha384_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  pg_sha512_update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

void
pg_sha384_update(pg_sha384_ctx *context, const uint8 *data, size_t len)
{
	pg_sha512_update((pg_sha512_ctx *) context, data, len);
}