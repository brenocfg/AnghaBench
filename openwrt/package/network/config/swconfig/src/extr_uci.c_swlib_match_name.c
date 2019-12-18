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
struct switch_dev {int /*<<< orphan*/  alias; int /*<<< orphan*/  dev_name; } ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool swlib_match_name(struct switch_dev *dev, const char *name)
{
	return (strcmp(name, dev->dev_name) == 0 ||
		strcmp(name, dev->alias) == 0);
}