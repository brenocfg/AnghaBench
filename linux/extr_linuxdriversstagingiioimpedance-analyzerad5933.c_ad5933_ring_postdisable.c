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
struct iio_dev {int dummy; } ;
struct ad5933_state {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD5933_CTRL_POWER_DOWN ; 
 int ad5933_cmd (struct ad5933_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct ad5933_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ad5933_ring_postdisable(struct iio_dev *indio_dev)
{
	struct ad5933_state *st = iio_priv(indio_dev);

	cancel_delayed_work_sync(&st->work);
	return ad5933_cmd(st, AD5933_CTRL_POWER_DOWN);
}