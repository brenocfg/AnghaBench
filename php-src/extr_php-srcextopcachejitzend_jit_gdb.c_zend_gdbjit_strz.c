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
struct TYPE_3__ {int startp; scalar_t__* p; } ;
typedef  TYPE_1__ zend_gdbjit_ctx ;
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t zend_gdbjit_strz(zend_gdbjit_ctx *ctx, const char *str)
{
	uint8_t *p = ctx->p;
	uint32_t ofs = (uint32_t)(p - ctx->startp);
	do {
		*p++ = (uint8_t)*str;
	} while (*str++);
	ctx->p = p;
	return ofs;
}