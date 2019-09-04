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
struct bq25890_device {int /*<<< orphan*/ * rmap_fields; } ;
typedef  enum bq25890_fields { ____Placeholder_bq25890_fields } bq25890_fields ;

/* Variables and functions */
 int regmap_field_read (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int bq25890_field_read(struct bq25890_device *bq,
			      enum bq25890_fields field_id)
{
	int ret;
	int val;

	ret = regmap_field_read(bq->rmap_fields[field_id], &val);
	if (ret < 0)
		return ret;

	return val;
}