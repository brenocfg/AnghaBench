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
struct gdIOCtx {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  php_stream ;

/* Variables and functions */
 int /*<<< orphan*/  php_stream_write (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void _php_image_stream_putc(struct gdIOCtx *ctx, int c) /* {{{ */ {
	char ch = (char) c;
	php_stream * stream = (php_stream *)ctx->data;
	php_stream_write(stream, &ch, 1);
}