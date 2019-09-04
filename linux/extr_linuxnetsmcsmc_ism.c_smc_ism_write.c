#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct smcd_dev {TYPE_1__* ops; } ;
struct smc_ism_position {int /*<<< orphan*/  offset; int /*<<< orphan*/  signal; int /*<<< orphan*/  index; int /*<<< orphan*/  token; } ;
struct TYPE_2__ {int (* move_data ) (struct smcd_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t) ;} ;

/* Variables and functions */
 int stub1 (struct smcd_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t) ; 

int smc_ism_write(struct smcd_dev *smcd, const struct smc_ism_position *pos,
		  void *data, size_t len)
{
	int rc;

	rc = smcd->ops->move_data(smcd, pos->token, pos->index, pos->signal,
				  pos->offset, data, len);

	return rc < 0 ? rc : 0;
}