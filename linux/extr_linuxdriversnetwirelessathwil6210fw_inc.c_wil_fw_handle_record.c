#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wil6210_priv {int dummy; } ;
struct TYPE_3__ {int type; int (* load_handler ) (struct wil6210_priv*,void const*,size_t) ;int (* parse_handler ) (struct wil6210_priv*,void const*,size_t) ;} ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int stub1 (struct wil6210_priv*,void const*,size_t) ; 
 int stub2 (struct wil6210_priv*,void const*,size_t) ; 
 int /*<<< orphan*/  wil_err_fw (struct wil6210_priv*,char*,int) ; 
 TYPE_1__* wil_fw_handlers ; 

__attribute__((used)) static int wil_fw_handle_record(struct wil6210_priv *wil, int type,
				const void *data, size_t size, bool load)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(wil_fw_handlers); i++)
		if (wil_fw_handlers[i].type == type)
			return load ?
				wil_fw_handlers[i].load_handler(
					wil, data, size) :
				wil_fw_handlers[i].parse_handler(
					wil, data, size);

	wil_err_fw(wil, "unknown record type: %d\n", type);
	return -EINVAL;
}