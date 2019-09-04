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
struct cris_disasm_data {int /*<<< orphan*/  distype; } ;
typedef  scalar_t__ bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  REGISTER_PREFIX_CHAR ; 
 int /*<<< orphan*/  cris_dis_v32 ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
format_reg (struct cris_disasm_data *disdata,
	    int regno,
	    char *outbuffer_start,
	    bfd_boolean with_reg_prefix)
{
  char *outbuffer = outbuffer_start;

  if (with_reg_prefix) {
	  *outbuffer++ = REGISTER_PREFIX_CHAR;
  }

  switch (regno)
    {
    case 15:
      /* For v32, there is no context in which we output PC.  */
      if (disdata->distype == cris_dis_v32) {
	      strcpy (outbuffer, "acr");
      } else {
	      strcpy (outbuffer, "pc");
      }
      break;

    case 14:
      strcpy (outbuffer, "sp");
      break;

    default:
      sprintf (outbuffer, "r%d", regno);
      break;
    }

  return outbuffer_start + strlen (outbuffer_start);
}