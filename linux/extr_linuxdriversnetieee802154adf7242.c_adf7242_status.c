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
typedef  int /*<<< orphan*/  u8 ;
struct adf7242_local {int /*<<< orphan*/  bmux; int /*<<< orphan*/  buf_stat_rx; int /*<<< orphan*/  stat_msg; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int spi_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adf7242_status(struct adf7242_local *lp, u8 *stat)
{
	int status;

	mutex_lock(&lp->bmux);
	status = spi_sync(lp->spi, &lp->stat_msg);
	*stat = lp->buf_stat_rx;
	mutex_unlock(&lp->bmux);

	return status;
}