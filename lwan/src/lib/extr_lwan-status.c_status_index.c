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
typedef  enum lwan_status_type { ____Placeholder_lwan_status_type } lwan_status_type ;

/* Variables and functions */
 int STATUS_NONE ; 
 scalar_t__ use_colors ; 

__attribute__((used)) static int status_index(enum lwan_status_type type)
{
    return use_colors ? (int)type : STATUS_NONE;
}