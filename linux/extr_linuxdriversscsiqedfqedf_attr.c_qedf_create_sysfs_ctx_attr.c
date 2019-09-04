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
struct qedf_ctx {TYPE_1__* lport; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  bin_file_entries ; 
 int /*<<< orphan*/  qedf_create_sysfs_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void qedf_create_sysfs_ctx_attr(struct qedf_ctx *qedf)
{
	qedf_create_sysfs_attr(qedf->lport->host, bin_file_entries);
}