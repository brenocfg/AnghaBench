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
struct tsens_sensor {char offset; } ;
struct tsens_device {int num_sensors; int /*<<< orphan*/  dev; struct tsens_sensor* sensor; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (char*) ; 
 int PTR_ERR (char*) ; 
 char* qfprom_read (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int calibrate_8960(struct tsens_device *tmdev)
{
	int i;
	char *data;

	ssize_t num_read = tmdev->num_sensors;
	struct tsens_sensor *s = tmdev->sensor;

	data = qfprom_read(tmdev->dev, "calib");
	if (IS_ERR(data))
		data = qfprom_read(tmdev->dev, "calib_backup");
	if (IS_ERR(data))
		return PTR_ERR(data);

	for (i = 0; i < num_read; i++, s++)
		s->offset = data[i];

	return 0;
}