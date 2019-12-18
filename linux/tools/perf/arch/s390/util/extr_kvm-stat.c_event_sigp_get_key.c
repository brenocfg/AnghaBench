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
struct perf_sample {int dummy; } ;
struct evsel {int dummy; } ;
struct event_key {int /*<<< orphan*/  exit_reasons; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_evsel__intval (struct evsel*,struct perf_sample*,char*) ; 
 int /*<<< orphan*/  sie_sigp_order_codes ; 

__attribute__((used)) static void event_sigp_get_key(struct evsel *evsel,
			       struct perf_sample *sample,
			       struct event_key *key)
{
	key->key = perf_evsel__intval(evsel, sample, "order_code");
	key->exit_reasons = sie_sigp_order_codes;
}