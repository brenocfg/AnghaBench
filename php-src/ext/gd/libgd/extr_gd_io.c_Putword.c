#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* putBuf ) (TYPE_1__*,char*,int) ;} ;
typedef  TYPE_1__ gdIOCtx ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*,int) ; 

void Putword (int w, gdIOCtx * ctx)
{
	unsigned char buf[2];

	buf[0] = w & 0xff;
	buf[1] = (w / 256) & 0xff;
	(ctx->putBuf) (ctx, (char *) buf, 2);
}