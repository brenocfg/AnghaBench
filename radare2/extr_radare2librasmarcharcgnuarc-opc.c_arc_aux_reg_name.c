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
struct TYPE_2__ {scalar_t__ type; int value; char* name; } ;

/* Variables and functions */
 scalar_t__ AUXREG_AC ; 
 TYPE_1__* arc_reg_names ; 
 int arc_reg_names_count ; 

char *
arc_aux_reg_name (int regVal)
{
  int i;

  for (i= arc_reg_names_count ; i > 0  ; i--)
    {
	  if ((arc_reg_names[i].type == AUXREG_AC) && (arc_reg_names[i].value == regVal)) {
		  return arc_reg_names[i].name;
	  }
    }

  return NULL;
}