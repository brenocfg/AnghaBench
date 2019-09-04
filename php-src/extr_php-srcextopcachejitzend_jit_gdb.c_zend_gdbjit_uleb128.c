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
struct TYPE_3__ {void** p; } ;
typedef  TYPE_1__ zend_gdbjit_ctx ;
typedef  void* uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static void zend_gdbjit_uleb128(zend_gdbjit_ctx *ctx, uint32_t v)
{
	uint8_t *p = ctx->p;
	for (; v >= 0x80; v >>= 7)
		*p++ = (uint8_t)((v & 0x7f) | 0x80);
	*p++ = (uint8_t)v;
	ctx->p = p;
}