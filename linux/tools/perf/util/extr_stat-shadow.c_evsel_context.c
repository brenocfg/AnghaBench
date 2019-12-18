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
struct TYPE_3__ {scalar_t__ exclude_idle; scalar_t__ exclude_host; scalar_t__ exclude_hv; scalar_t__ exclude_user; scalar_t__ exclude_kernel; } ;
struct TYPE_4__ {TYPE_1__ attr; } ;
struct evsel {TYPE_2__ core; } ;

/* Variables and functions */
 int CTX_BIT_HOST ; 
 int CTX_BIT_HV ; 
 int CTX_BIT_IDLE ; 
 int CTX_BIT_KERNEL ; 
 int CTX_BIT_USER ; 

__attribute__((used)) static int evsel_context(struct evsel *evsel)
{
	int ctx = 0;

	if (evsel->core.attr.exclude_kernel)
		ctx |= CTX_BIT_KERNEL;
	if (evsel->core.attr.exclude_user)
		ctx |= CTX_BIT_USER;
	if (evsel->core.attr.exclude_hv)
		ctx |= CTX_BIT_HV;
	if (evsel->core.attr.exclude_host)
		ctx |= CTX_BIT_HOST;
	if (evsel->core.attr.exclude_idle)
		ctx |= CTX_BIT_IDLE;

	return ctx;
}