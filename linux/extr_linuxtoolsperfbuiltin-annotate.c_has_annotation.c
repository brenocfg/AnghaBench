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
struct perf_annotate {scalar_t__ use_stdio2; } ;

/* Variables and functions */
 scalar_t__ ui__has_annotation () ; 

__attribute__((used)) static bool has_annotation(struct perf_annotate *ann)
{
	return ui__has_annotation() || ann->use_stdio2;
}