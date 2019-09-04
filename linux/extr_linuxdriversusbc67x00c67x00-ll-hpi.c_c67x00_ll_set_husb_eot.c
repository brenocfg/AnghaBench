#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_4__ {TYPE_1__ lcp; } ;
struct c67x00_device {TYPE_2__ hpi; } ;

/* Variables and functions */
 int /*<<< orphan*/  HUSB_pEOT ; 
 int /*<<< orphan*/  hpi_write_word (struct c67x00_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void c67x00_ll_set_husb_eot(struct c67x00_device *dev, u16 value)
{
	mutex_lock(&dev->hpi.lcp.mutex);
	hpi_write_word(dev, HUSB_pEOT, value);
	mutex_unlock(&dev->hpi.lcp.mutex);
}