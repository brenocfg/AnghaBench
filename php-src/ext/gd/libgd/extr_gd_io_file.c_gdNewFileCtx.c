#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gdIOCtx ;
struct TYPE_3__ {int /*<<< orphan*/  gd_free; int /*<<< orphan*/  seek; int /*<<< orphan*/  tell; int /*<<< orphan*/  putBuf; int /*<<< orphan*/  getBuf; int /*<<< orphan*/  putC; int /*<<< orphan*/  getC; } ;
struct TYPE_4__ {TYPE_1__ ctx; int /*<<< orphan*/ * f; } ;
typedef  TYPE_2__ fileIOCtx ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fileGetbuf ; 
 int /*<<< orphan*/  fileGetchar ; 
 int /*<<< orphan*/  filePutbuf ; 
 int /*<<< orphan*/  filePutchar ; 
 int /*<<< orphan*/  fileSeek ; 
 int /*<<< orphan*/  fileTell ; 
 int /*<<< orphan*/  gdFreeFileCtx ; 
 scalar_t__ gdMalloc (int) ; 

gdIOCtx * gdNewFileCtx (FILE * f)
{
	fileIOCtx *ctx;

	ctx = (fileIOCtx *) gdMalloc(sizeof (fileIOCtx));

	ctx->f = f;

	ctx->ctx.getC = fileGetchar;
	ctx->ctx.putC = filePutchar;

	ctx->ctx.getBuf = fileGetbuf;
	ctx->ctx.putBuf = filePutbuf;

	ctx->ctx.tell = fileTell;
	ctx->ctx.seek = fileSeek;

	ctx->ctx.gd_free = gdFreeFileCtx;

	return (gdIOCtx *) ctx;
}