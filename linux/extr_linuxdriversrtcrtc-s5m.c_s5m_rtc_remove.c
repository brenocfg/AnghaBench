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
struct s5m_rtc_info {int /*<<< orphan*/  i2c; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 
 struct s5m_rtc_info* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int s5m_rtc_remove(struct platform_device *pdev)
{
	struct s5m_rtc_info *info = platform_get_drvdata(pdev);

	i2c_unregister_device(info->i2c);

	return 0;
}