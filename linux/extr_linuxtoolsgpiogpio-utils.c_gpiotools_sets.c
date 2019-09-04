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
struct gpiohandle_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMSUMER ; 
 int /*<<< orphan*/  GPIOHANDLE_REQUEST_OUTPUT ; 
 int gpiotools_release_linehandle (int) ; 
 int gpiotools_request_linehandle (char const*,unsigned int*,unsigned int,int /*<<< orphan*/ ,struct gpiohandle_data*,int /*<<< orphan*/ ) ; 

int gpiotools_sets(const char *device_name, unsigned int *lines,
		   unsigned int nlines, struct gpiohandle_data *data)
{
	int ret;

	ret = gpiotools_request_linehandle(device_name, lines, nlines,
					   GPIOHANDLE_REQUEST_OUTPUT, data,
					   COMSUMER);
	if (ret < 0)
		return ret;

	return gpiotools_release_linehandle(ret);
}