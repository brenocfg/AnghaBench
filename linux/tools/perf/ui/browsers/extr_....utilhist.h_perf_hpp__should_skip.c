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
struct perf_hpp_fmt {scalar_t__ elide; } ;
struct hists {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_hpp__defined_dynamic_entry (struct perf_hpp_fmt*,struct hists*) ; 
 scalar_t__ perf_hpp__is_dynamic_entry (struct perf_hpp_fmt*) ; 

__attribute__((used)) static inline bool perf_hpp__should_skip(struct perf_hpp_fmt *format,
					 struct hists *hists)
{
	if (format->elide)
		return true;

	if (perf_hpp__is_dynamic_entry(format) &&
	    !perf_hpp__defined_dynamic_entry(format, hists))
		return true;

	return false;
}