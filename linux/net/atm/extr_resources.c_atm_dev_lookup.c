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
struct atm_dev {int dummy; } ;

/* Variables and functions */
 struct atm_dev* __atm_dev_lookup (int) ; 
 int /*<<< orphan*/  atm_dev_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct atm_dev *atm_dev_lookup(int number)
{
	struct atm_dev *dev;

	mutex_lock(&atm_dev_mutex);
	dev = __atm_dev_lookup(number);
	mutex_unlock(&atm_dev_mutex);
	return dev;
}