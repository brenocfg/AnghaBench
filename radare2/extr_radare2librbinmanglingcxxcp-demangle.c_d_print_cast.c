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
struct demangle_component {int dummy; } ;
struct d_print_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_left (struct demangle_component*) ; 
 int /*<<< orphan*/  d_print_comp (struct d_print_info*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
d_print_cast (struct d_print_info *dpi, int options,
	      struct demangle_component *dc)
{
  d_print_comp (dpi, options, d_left (dc));
}