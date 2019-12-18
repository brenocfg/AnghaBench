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
struct ExtAuxRegister {long address; scalar_t__ name; struct ExtAuxRegister* next; } ;
struct TYPE_2__ {struct ExtAuxRegister* auxRegisters; } ;

/* Variables and functions */
 TYPE_1__ arc_extension_map ; 

const char *
arcExtMap_auxRegName (long address)
{
  /* Walk the list of auxiliary register names and find the name.  */
  struct ExtAuxRegister *r;

  for (r = arc_extension_map.auxRegisters; r; r = r->next)
    {
	  if (r->address == address) {
		  return (const char *)r->name;
	  }
    }
  return NULL;
}