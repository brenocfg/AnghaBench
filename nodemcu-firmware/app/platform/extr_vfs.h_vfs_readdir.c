#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* fns; } ;
typedef  TYPE_2__ vfs_dir ;
struct vfs_stat {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* readdir ) (TYPE_2__*,struct vfs_stat*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct vfs_stat*) ; 

__attribute__((used)) static int32_t vfs_readdir( vfs_dir *dd, struct vfs_stat *buf ) { return dd->fns->readdir( dd, buf ); }