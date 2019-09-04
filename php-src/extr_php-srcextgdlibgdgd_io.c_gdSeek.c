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
struct TYPE_4__ {int (* seek ) (TYPE_1__*,int const) ;} ;
typedef  TYPE_1__ gdIOCtx ;

/* Variables and functions */
 int /*<<< orphan*/  IO_DBG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gd_error (char*) ; 
 int stub1 (TYPE_1__*,int const) ; 

int gdSeek (gdIOCtx * ctx, const int pos)
{
	IO_DBG (gd_error("Seeking..."));
	return ((ctx->seek) (ctx, pos));
	IO_DBG (gd_error("Done."));
}