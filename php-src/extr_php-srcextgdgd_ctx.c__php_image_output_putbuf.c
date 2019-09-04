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
 int php_write (void*,int) ; 

__attribute__((used)) static int _php_image_output_putbuf(struct gdIOCtx *ctx, const void* buf, int l) /* {{{ */
{
	return php_write((void *)buf, l);
}