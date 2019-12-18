#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  number; } ;
struct TYPE_6__ {TYPE_2__ s_number; } ;
struct demangle_component {TYPE_3__ u; } ;
struct d_print_info {TYPE_1__* templates; } ;
struct TYPE_4__ {int /*<<< orphan*/  template_decl; } ;

/* Variables and functions */
 struct demangle_component* d_index_template_argument (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_print_error (struct d_print_info*) ; 
 int /*<<< orphan*/  d_right (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct demangle_component *
d_lookup_template_argument (struct d_print_info *dpi,
			    const struct demangle_component *dc)
{
  if (dpi->templates == NULL)
    {
      d_print_error (dpi);
      return NULL;
    }
	
  return d_index_template_argument
    (d_right (dpi->templates->template_decl),
     dc->u.s_number.number);
}