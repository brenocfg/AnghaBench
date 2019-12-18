#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  st_nlink; int /*<<< orphan*/  st_size; void* st_ctime; void* st_mtime; void* st_atime; int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_dev; scalar_t__ st_gid; scalar_t__ st_uid; } ;
typedef  TYPE_3__ zend_stat_t ;
struct TYPE_10__ {TYPE_3__ finfo; TYPE_2__* r; } ;
typedef  TYPE_4__ php_struct ;
struct TYPE_7__ {int /*<<< orphan*/  nlink; int /*<<< orphan*/  size; int /*<<< orphan*/  ctime; int /*<<< orphan*/  mtime; int /*<<< orphan*/  atime; int /*<<< orphan*/  inode; int /*<<< orphan*/  device; scalar_t__ group; scalar_t__ user; } ;
struct TYPE_8__ {TYPE_1__ finfo; } ;

/* Variables and functions */
 TYPE_4__* SG (int /*<<< orphan*/ ) ; 
 void* apr_time_sec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_context ; 

__attribute__((used)) static zend_stat_t*
php_apache_sapi_get_stat(void)
{
	php_struct *ctx = SG(server_context);

#ifdef PHP_WIN32
	ctx->finfo.st_uid = 0;
	ctx->finfo.st_gid = 0;
#else
	ctx->finfo.st_uid = ctx->r->finfo.user;
	ctx->finfo.st_gid = ctx->r->finfo.group;
#endif
	ctx->finfo.st_dev = ctx->r->finfo.device;
	ctx->finfo.st_ino = ctx->r->finfo.inode;
	ctx->finfo.st_atime = apr_time_sec(ctx->r->finfo.atime);
	ctx->finfo.st_mtime = apr_time_sec(ctx->r->finfo.mtime);
	ctx->finfo.st_ctime = apr_time_sec(ctx->r->finfo.ctime);
	ctx->finfo.st_size = ctx->r->finfo.size;
	ctx->finfo.st_nlink = ctx->r->finfo.nlink;

	return &ctx->finfo;
}