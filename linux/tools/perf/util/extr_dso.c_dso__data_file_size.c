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
struct TYPE_2__ {scalar_t__ status; scalar_t__ file_size; } ;
struct dso {scalar_t__ binary_type; TYPE_1__ data; } ;

/* Variables and functions */
 scalar_t__ DSO_BINARY_TYPE__BPF_PROG_INFO ; 
 scalar_t__ DSO_DATA_STATUS_ERROR ; 
 int bpf_size (struct dso*) ; 
 int file_size (struct dso*,struct machine*) ; 

int dso__data_file_size(struct dso *dso, struct machine *machine)
{
	if (dso->data.file_size)
		return 0;

	if (dso->data.status == DSO_DATA_STATUS_ERROR)
		return -1;

	if (dso->binary_type == DSO_BINARY_TYPE__BPF_PROG_INFO)
		return bpf_size(dso);

	return file_size(dso, machine);
}