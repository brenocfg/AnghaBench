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
struct s6e63m0 {int gamma_table_count; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct s6e63m0* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static ssize_t s6e63m0_sysfs_show_gamma_table(struct device *dev,
				      struct device_attribute *attr, char *buf)
{
	struct s6e63m0 *lcd = dev_get_drvdata(dev);
	char temp[3];

	sprintf(temp, "%u\n", lcd->gamma_table_count);
	strcpy(buf, temp);

	return strlen(buf);
}