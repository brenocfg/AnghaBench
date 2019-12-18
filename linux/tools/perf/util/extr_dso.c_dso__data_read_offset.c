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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct machine {int dummy; } ;
struct TYPE_2__ {scalar_t__ status; } ;
struct dso {TYPE_1__ data; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ DSO_DATA_STATUS_ERROR ; 
 int data_read_offset (struct dso*,struct machine*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

ssize_t dso__data_read_offset(struct dso *dso, struct machine *machine,
			      u64 offset, u8 *data, ssize_t size)
{
	if (dso->data.status == DSO_DATA_STATUS_ERROR)
		return -1;

	return data_read_offset(dso, machine, offset, data, size);
}