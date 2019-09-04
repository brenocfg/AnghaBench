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
struct cpu_map {int dummy; } ;
struct TYPE_6__ {TYPE_2__* session; } ;
struct TYPE_4__ {int /*<<< orphan*/  env; } ;
struct TYPE_5__ {TYPE_1__ header; } ;

/* Variables and functions */
 int perf_env__get_socket (struct cpu_map*,int,int /*<<< orphan*/ *) ; 
 TYPE_3__ perf_stat ; 

__attribute__((used)) static int perf_stat__get_socket_file(struct cpu_map *map, int idx)
{
	return perf_env__get_socket(map, idx, &perf_stat.session->header.env);
}