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
struct TYPE_2__ {int /*<<< orphan*/  (* uninit ) (int /*<<< orphan*/ ) ;} ;
struct wil6210_priv {TYPE_1__ platform_ops; int /*<<< orphan*/  platform_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wil_platform_ops_uninit(struct wil6210_priv *wil)
{
	if (wil->platform_ops.uninit)
		wil->platform_ops.uninit(wil->platform_handle);
	memset(&wil->platform_ops, 0, sizeof(wil->platform_ops));
}