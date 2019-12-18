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
struct lwan_value {int dummy; } ;
typedef  enum lwan_status_type { ____Placeholder_lwan_status_type } lwan_status_type ;

/* Variables and functions */
 struct lwan_value* start_colors ; 
 size_t status_index (int) ; 

__attribute__((used)) static inline struct lwan_value start_color(enum lwan_status_type type)
{
    return start_colors[status_index(type)];
}