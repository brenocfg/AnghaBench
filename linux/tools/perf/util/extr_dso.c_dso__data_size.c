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
struct machine {int dummy; } ;
struct TYPE_2__ {int file_size; } ;
struct dso {TYPE_1__ data; } ;
typedef  int off_t ;

/* Variables and functions */
 scalar_t__ dso__data_file_size (struct dso*,struct machine*) ; 

off_t dso__data_size(struct dso *dso, struct machine *machine)
{
	if (dso__data_file_size(dso, machine))
		return -1;

	/* For now just estimate dso data size is close to file size */
	return dso->data.file_size;
}