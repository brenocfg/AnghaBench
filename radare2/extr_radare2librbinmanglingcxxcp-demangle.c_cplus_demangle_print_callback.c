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
struct d_print_info {int num_saved_scopes; int num_copy_templates; void* copy_templates; void* saved_scopes; } ;
typedef  int /*<<< orphan*/  demangle_callbackref ;

/* Variables and functions */
 void* alloca (int) ; 
 int /*<<< orphan*/  d_print_comp (struct d_print_info*,int,struct demangle_component*) ; 
 int /*<<< orphan*/  d_print_flush (struct d_print_info*) ; 
 int /*<<< orphan*/  d_print_init (struct d_print_info*,int /*<<< orphan*/ ,void*,struct demangle_component*) ; 
 int /*<<< orphan*/  d_print_saw_error (struct d_print_info*) ; 

int
cplus_demangle_print_callback (int options,
                               struct demangle_component *dc,
                               demangle_callbackref callback, void *opaque)
{
  struct d_print_info dpi;

  d_print_init (&dpi, callback, opaque, dc);

  {
#ifdef CP_DYNAMIC_ARRAYS
    /* Avoid zero-length VLAs, which are prohibited by the C99 standard
       and flagged as errors by Address Sanitizer.  */
    __extension__ struct d_saved_scope scopes[(dpi.num_saved_scopes > 0)
                                              ? dpi.num_saved_scopes : 1];
    __extension__ struct d_print_template temps[(dpi.num_copy_templates > 0)
                                                ? dpi.num_copy_templates : 1];

    dpi.saved_scopes = scopes;
    dpi.copy_templates = temps;
#else
    dpi.saved_scopes = alloca (dpi.num_saved_scopes
			       * sizeof (*dpi.saved_scopes));
    dpi.copy_templates = alloca (dpi.num_copy_templates
				 * sizeof (*dpi.copy_templates));
#endif

    d_print_comp (&dpi, options, dc);
  }

  d_print_flush (&dpi);

  return ! d_print_saw_error (&dpi);
}