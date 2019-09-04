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
struct ftrace_event_field {scalar_t__ filter_type; } ;

/* Variables and functions */
 scalar_t__ FILTER_COMM ; 
 scalar_t__ FILTER_DYN_STRING ; 
 scalar_t__ FILTER_PTR_STRING ; 
 scalar_t__ FILTER_STATIC_STRING ; 

__attribute__((used)) static inline bool is_string_field(struct ftrace_event_field *field)
{
	return field->filter_type == FILTER_DYN_STRING ||
	       field->filter_type == FILTER_STATIC_STRING ||
	       field->filter_type == FILTER_PTR_STRING ||
	       field->filter_type == FILTER_COMM;
}