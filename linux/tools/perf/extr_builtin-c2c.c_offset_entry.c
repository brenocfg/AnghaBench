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
typedef  int /*<<< orphan*/  uint64_t ;
struct perf_hpp_fmt {int dummy; } ;
struct perf_hpp {int /*<<< orphan*/  size; int /*<<< orphan*/  buf; } ;
struct hist_entry {TYPE_2__* mem_info; int /*<<< orphan*/  hists; } ;
struct TYPE_3__ {int /*<<< orphan*/  al_addr; } ;
struct TYPE_4__ {TYPE_1__ daddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEX_STR (char*,int /*<<< orphan*/ ) ; 
 int c2c_width (struct perf_hpp_fmt*,struct perf_hpp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_offset (int /*<<< orphan*/ ) ; 
 int scnprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int offset_entry(struct perf_hpp_fmt *fmt, struct perf_hpp *hpp,
			struct hist_entry *he)
{
	uint64_t addr = 0;
	int width = c2c_width(fmt, hpp, he->hists);
	char buf[20];

	if (he->mem_info)
		addr = cl_offset(he->mem_info->daddr.al_addr);

	return scnprintf(hpp->buf, hpp->size, "%*s", width, HEX_STR(buf, addr));
}