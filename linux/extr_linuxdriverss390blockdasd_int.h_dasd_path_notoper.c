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
struct dasd_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dasd_path_clear_nonpreferred (struct dasd_device*,int) ; 
 int /*<<< orphan*/  dasd_path_clear_oper (struct dasd_device*,int) ; 
 int /*<<< orphan*/  dasd_path_clear_preferred (struct dasd_device*,int) ; 

__attribute__((used)) static inline void dasd_path_notoper(struct dasd_device *device, int chp)
{
	dasd_path_clear_oper(device, chp);
	dasd_path_clear_preferred(device, chp);
	dasd_path_clear_nonpreferred(device, chp);
}