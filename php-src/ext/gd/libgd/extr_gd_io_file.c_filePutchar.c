#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gdIOCtx ;
struct TYPE_2__ {int /*<<< orphan*/  f; } ;
typedef  TYPE_1__ fileIOCtx ;

/* Variables and functions */
 int /*<<< orphan*/  putc (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void filePutchar (gdIOCtx * ctx, int a)
{
	unsigned char b;
	fileIOCtx *fctx;
	fctx = (fileIOCtx *) ctx;

	b = a;

	putc (b, fctx->f);
}