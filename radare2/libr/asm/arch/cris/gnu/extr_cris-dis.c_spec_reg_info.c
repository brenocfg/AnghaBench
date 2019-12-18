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
struct cris_spec_reg {unsigned int number; int applicable_version; int /*<<< orphan*/  warning; int /*<<< orphan*/ * name; } ;
typedef  enum cris_disass_family { ____Placeholder_cris_disass_family } cris_disass_family ;

/* Variables and functions */
 int cris_dis_v32 ; 
 struct cris_spec_reg const* cris_spec_regs ; 
#define  cris_ver_v10p 133 
#define  cris_ver_v32p 132 
#define  cris_ver_v3p 131 
#define  cris_ver_v8p 130 
#define  cris_ver_version_all 129 
#define  cris_ver_warning 128 

__attribute__((used)) static const struct cris_spec_reg *
spec_reg_info (unsigned int sreg, enum cris_disass_family distype)
{
  int i;

  for (i = 0; cris_spec_regs[i].name != NULL; i++)
    {
      if (cris_spec_regs[i].number == sreg)
	{
	      if (distype == cris_dis_v32) {
		      switch (cris_spec_regs[i].applicable_version) {
		      case cris_ver_warning:
		      case cris_ver_version_all:
		      case cris_ver_v3p:
		      case cris_ver_v8p:
		      case cris_ver_v10p:
		      case cris_ver_v32p:
			      /* No ambiguous sizes or register names with CRISv32.  */
			      if (!cris_spec_regs[i].warning) {
				      return &cris_spec_regs[i];
			      }
		      default:;
		      }
	      } else if (cris_spec_regs[i].applicable_version != cris_ver_v32p) {
		      return &cris_spec_regs[i];
	      }
	}
    }

  return NULL;
}