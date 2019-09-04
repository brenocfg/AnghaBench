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
struct format_data_t {int dummy; } ;
struct dasd_device {int dummy; } ;

/* Variables and functions */
 int dasd_eckd_format_process_data (struct dasd_device*,struct format_data_t*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dasd_eckd_format_device(struct dasd_device *base,
				   struct format_data_t *fdata, int enable_pav)
{
	return dasd_eckd_format_process_data(base, fdata, enable_pav, 0, NULL,
					     0, NULL);
}