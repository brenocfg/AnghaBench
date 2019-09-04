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
struct path {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  actor; } ;
struct ovl_readdir_data {int d_type_supported; TYPE_1__ ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ovl_check_d_type ; 
 int ovl_dir_read (struct path*,struct ovl_readdir_data*) ; 

int ovl_check_d_type_supported(struct path *realpath)
{
	int err;
	struct ovl_readdir_data rdd = {
		.ctx.actor = ovl_check_d_type,
		.d_type_supported = false,
	};

	err = ovl_dir_read(realpath, &rdd);
	if (err)
		return err;

	return rdd.d_type_supported;
}