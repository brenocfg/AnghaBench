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
struct regulator {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPTIONAL_GET ; 
 struct regulator* _regulator_get (struct device*,char const*,int /*<<< orphan*/ ) ; 

struct regulator *regulator_get_optional(struct device *dev, const char *id)
{
	return _regulator_get(dev, id, OPTIONAL_GET);
}