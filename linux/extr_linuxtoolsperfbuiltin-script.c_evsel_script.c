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
struct perf_evsel_script {int dummy; } ;
struct perf_evsel {scalar_t__ priv; } ;

/* Variables and functions */

__attribute__((used)) static inline struct perf_evsel_script *evsel_script(struct perf_evsel *evsel)
{
	return (struct perf_evsel_script *)evsel->priv;
}