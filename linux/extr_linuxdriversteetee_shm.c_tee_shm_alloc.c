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
typedef  int /*<<< orphan*/  u32 ;
struct tee_shm {int dummy; } ;
struct tee_context {int /*<<< orphan*/  teedev; } ;

/* Variables and functions */
 struct tee_shm* __tee_shm_alloc (struct tee_context*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

struct tee_shm *tee_shm_alloc(struct tee_context *ctx, size_t size, u32 flags)
{
	return __tee_shm_alloc(ctx, ctx->teedev, size, flags);
}