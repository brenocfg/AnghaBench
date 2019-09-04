#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_2__* device; } ;
struct TYPE_6__ {int msgout_len; int /*<<< orphan*/ * msgoutbuf; } ;
typedef  TYPE_3__ nsp32_hw_data ;
struct TYPE_5__ {TYPE_1__* host; } ;
struct TYPE_4__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  MESSAGE_REJECT ; 

__attribute__((used)) static void nsp32_build_reject(struct scsi_cmnd *SCpnt)
{
	nsp32_hw_data *data = (nsp32_hw_data *)SCpnt->device->host->hostdata;
	int            pos  = data->msgout_len;

	data->msgoutbuf[pos] = MESSAGE_REJECT; pos++;
	data->msgout_len = pos;
}