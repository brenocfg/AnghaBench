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
struct wl1251 {int /*<<< orphan*/ * data_path; } ;
struct acx_data_path_params_resp {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_acx_data_path_params (struct wl1251*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wl1251_hw_init_data_path_config(struct wl1251 *wl)
{
	int ret;

	/* asking for the data path parameters */
	wl->data_path = kzalloc(sizeof(struct acx_data_path_params_resp),
				GFP_KERNEL);
	if (!wl->data_path)
		return -ENOMEM;

	ret = wl1251_acx_data_path_params(wl, wl->data_path);
	if (ret < 0) {
		kfree(wl->data_path);
		wl->data_path = NULL;
		return ret;
	}

	return 0;
}