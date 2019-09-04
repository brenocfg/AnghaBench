#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  zfree; int /*<<< orphan*/  zalloc; } ;
struct TYPE_5__ {TYPE_1__ Z; } ;
typedef  TYPE_2__ php_zlib_context ;

/* Variables and functions */
 scalar_t__ ecalloc (int,int) ; 
 int /*<<< orphan*/  php_zlib_alloc ; 
 int /*<<< orphan*/  php_zlib_free ; 

__attribute__((used)) static php_zlib_context *php_zlib_output_handler_context_init(void)
{
	php_zlib_context *ctx = (php_zlib_context *) ecalloc(1, sizeof(php_zlib_context));
	ctx->Z.zalloc = php_zlib_alloc;
	ctx->Z.zfree = php_zlib_free;
	return ctx;
}