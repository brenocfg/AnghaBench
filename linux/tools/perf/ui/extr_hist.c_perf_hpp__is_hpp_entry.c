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
struct perf_hpp_fmt {scalar_t__ header; } ;

/* Variables and functions */
 scalar_t__ hpp__header_fn ; 

__attribute__((used)) static bool perf_hpp__is_hpp_entry(struct perf_hpp_fmt *a)
{
	return a->header == hpp__header_fn;
}