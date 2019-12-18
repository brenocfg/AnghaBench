#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct thread {int dummy; } ;
struct machine {int dummy; } ;
struct addr_location {TYPE_2__* map; } ;
struct TYPE_5__ {scalar_t__ status; } ;
struct TYPE_7__ {int is_64_bit; TYPE_1__ data; } ;
struct TYPE_6__ {long (* map_ip ) (TYPE_2__*,int /*<<< orphan*/ ) ;TYPE_4__* dso; } ;

/* Variables and functions */
 scalar_t__ DSO_DATA_STATUS_ERROR ; 
 int /*<<< orphan*/  PERF_RECORD_MISC_KERNEL ; 
 int /*<<< orphan*/  PERF_RECORD_MISC_USER ; 
 int dso__data_read_offset (TYPE_4__*,struct machine*,long,void*,int) ; 
 scalar_t__ machine__kernel_ip (struct machine*,int /*<<< orphan*/ ) ; 
 scalar_t__ map__load (TYPE_2__*) ; 
 long stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread__find_map (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct addr_location*) ; 

int thread__memcpy(struct thread *thread, struct machine *machine,
		   void *buf, u64 ip, int len, bool *is64bit)
{
       u8 cpumode = PERF_RECORD_MISC_USER;
       struct addr_location al;
       long offset;

       if (machine__kernel_ip(machine, ip))
               cpumode = PERF_RECORD_MISC_KERNEL;

       if (!thread__find_map(thread, cpumode, ip, &al) || !al.map->dso ||
	   al.map->dso->data.status == DSO_DATA_STATUS_ERROR ||
	   map__load(al.map) < 0)
               return -1;

       offset = al.map->map_ip(al.map, ip);
       if (is64bit)
               *is64bit = al.map->dso->is_64_bit;

       return dso__data_read_offset(al.map->dso, machine, offset, buf, len);
}