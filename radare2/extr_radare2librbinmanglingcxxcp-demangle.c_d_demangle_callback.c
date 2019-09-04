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
struct d_info {int num_comps; int num_subs; void* subs; void* comps; } ;
typedef  int /*<<< orphan*/  demangle_callbackref ;

/* Variables and functions */
 int /*<<< orphan*/  DEMANGLE_COMPONENT_GLOBAL_CONSTRUCTORS ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_GLOBAL_DESTRUCTORS ; 
 int DMGL_PARAMS ; 
 int DMGL_TYPES ; 
 int /*<<< orphan*/  abort () ; 
 void* alloca (int) ; 
 int /*<<< orphan*/  cplus_demangle_init_info (char const*,int,int,struct d_info*) ; 
 struct demangle_component* cplus_demangle_mangled_name (struct d_info*,int) ; 
 int cplus_demangle_print_callback (int,struct demangle_component*,int /*<<< orphan*/ ,void*) ; 
 struct demangle_component* cplus_demangle_type (struct d_info*) ; 
 int /*<<< orphan*/  d_advance (struct d_info*,int) ; 
 struct demangle_component* d_make_comp (struct d_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_make_demangle_mangled_name (struct d_info*,char const*) ; 
 char d_peek_char (struct d_info*) ; 
 char const* d_str (struct d_info*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static int
d_demangle_callback (const char *mangled, int options,
                     demangle_callbackref callback, void *opaque)
{
  enum
    {
      DCT_TYPE,
      DCT_MANGLED,
      DCT_GLOBAL_CTORS,
      DCT_GLOBAL_DTORS
    }
  type;
  struct d_info di;
  struct demangle_component *dc;
  int status;

  if (mangled[0] == '_' && mangled[1] == 'Z')
    type = DCT_MANGLED;
  else if (strncmp (mangled, "_GLOBAL_", 8) == 0
	   && (mangled[8] == '.' || mangled[8] == '_' || mangled[8] == '$')
	   && (mangled[9] == 'D' || mangled[9] == 'I')
	   && mangled[10] == '_')
    type = mangled[9] == 'I' ? DCT_GLOBAL_CTORS : DCT_GLOBAL_DTORS;
  else
    {
      if ((options & DMGL_TYPES) == 0)
	return 0;
      type = DCT_TYPE;
    }

  cplus_demangle_init_info (mangled, options, strlen (mangled), &di);

  {
#ifdef CP_DYNAMIC_ARRAYS
    __extension__ struct demangle_component comps[di.num_comps];
    __extension__ struct demangle_component *subs[di.num_subs];

    di.comps = comps;
    di.subs = subs;
#else
    di.comps = alloca (di.num_comps * sizeof (*di.comps));
    di.subs = alloca (di.num_subs * sizeof (*di.subs));
#endif

    switch (type)
      {
      case DCT_TYPE:
	dc = cplus_demangle_type (&di);
	break;
      case DCT_MANGLED:
	dc = cplus_demangle_mangled_name (&di, 1);
	break;
      case DCT_GLOBAL_CTORS:
      case DCT_GLOBAL_DTORS:
	d_advance (&di, 11);
	dc = d_make_comp (&di,
			  (type == DCT_GLOBAL_CTORS
			   ? DEMANGLE_COMPONENT_GLOBAL_CONSTRUCTORS
			   : DEMANGLE_COMPONENT_GLOBAL_DESTRUCTORS),
			  d_make_demangle_mangled_name (&di, d_str (&di)),
			  NULL);
	d_advance (&di, strlen (d_str (&di)));
	break;
      default:
	abort (); /* We have listed all the cases.  */
      }

    /* If DMGL_PARAMS is set, then if we didn't consume the entire
       mangled string, then we didn't successfully demangle it.  If
       DMGL_PARAMS is not set, we didn't look at the trailing
       parameters.  */
    if (((options & DMGL_PARAMS) != 0) && d_peek_char (&di) != '\0')
      dc = NULL;

#ifdef CP_DEMANGLE_DEBUG
    d_dump (dc, 0);
#endif

    status = (dc != NULL)
             ? cplus_demangle_print_callback (options, dc, callback, opaque)
             : 0;
  }

  return status;
}