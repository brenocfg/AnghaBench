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
struct source_location {int dummy; } ;
struct TYPE_2__ {scalar_t__ in_ubsan; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 scalar_t__ was_reported (struct source_location*) ; 

__attribute__((used)) static bool suppress_report(struct source_location *loc)
{
	return current->in_ubsan || was_reported(loc);
}