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
struct wimax_dev {int dummy; } ;
struct i2400m_reset_ctx {int result; int /*<<< orphan*/  completion; } ;
struct i2400m {int /*<<< orphan*/  init_mutex; struct i2400m_reset_ctx* reset_ctx; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPLETION_INITIALIZER_ONSTACK (int /*<<< orphan*/ ) ; 
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  I2400M_RT_WARM ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct wimax_dev*,int) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct wimax_dev*) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 int i2400m_reset (struct i2400m*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 
 struct i2400m* wimax_dev_to_i2400m (struct wimax_dev*) ; 

__attribute__((used)) static
int i2400m_op_reset(struct wimax_dev *wimax_dev)
{
	int result;
	struct i2400m *i2400m = wimax_dev_to_i2400m(wimax_dev);
	struct device *dev = i2400m_dev(i2400m);
	struct i2400m_reset_ctx ctx = {
		.completion = COMPLETION_INITIALIZER_ONSTACK(ctx.completion),
		.result = 0,
	};

	d_fnstart(4, dev, "(wimax_dev %p)\n", wimax_dev);
	mutex_lock(&i2400m->init_mutex);
	i2400m->reset_ctx = &ctx;
	mutex_unlock(&i2400m->init_mutex);
	result = i2400m_reset(i2400m, I2400M_RT_WARM);
	if (result < 0)
		goto out;
	result = wait_for_completion_timeout(&ctx.completion, 4*HZ);
	if (result == 0)
		result = -ETIMEDOUT;
	else if (result > 0)
		result = ctx.result;
	/* if result < 0, pass it on */
	mutex_lock(&i2400m->init_mutex);
	i2400m->reset_ctx = NULL;
	mutex_unlock(&i2400m->init_mutex);
out:
	d_fnend(4, dev, "(wimax_dev %p) = %d\n", wimax_dev, result);
	return result;
}