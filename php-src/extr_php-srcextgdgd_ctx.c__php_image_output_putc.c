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
struct gdIOCtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  php_write (unsigned char*,int) ; 

__attribute__((used)) static void _php_image_output_putc(struct gdIOCtx *ctx, int c) /* {{{ */
{
	/* without the following downcast, the write will fail
	 * (i.e., will write a zero byte) for all
	 * big endian architectures:
	 */
	unsigned char ch = (unsigned char) c;
	php_write(&ch, 1);
}