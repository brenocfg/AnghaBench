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
struct nfs_open_context {int mode; } ;
typedef  int fmode_t ;

/* Variables and functions */
 int FMODE_EXEC ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 

__attribute__((used)) static fmode_t _nfs4_ctx_to_openmode(const struct nfs_open_context *ctx)
{
	fmode_t ret = ctx->mode & (FMODE_READ|FMODE_WRITE);

	return (ctx->mode & FMODE_EXEC) ? FMODE_READ | ret : ret;
}