#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* bc_num ;
struct TYPE_4__ {int n_len; int n_scale; char* n_value; } ;

/* Variables and functions */
 TYPE_1__* BCG (int /*<<< orphan*/ ) ; 
 char FALSE ; 
 char TRUE ; 
 int /*<<< orphan*/  _zero_ ; 

char
bc_is_zero (bc_num num)
{
  int  count;
  char *nptr;

  /* Quick check. */
  if (num == BCG(_zero_)) return TRUE;

  /* Initialize */
  count = num->n_len + num->n_scale;
  nptr = num->n_value;

  /* The check */
  while ((count > 0) && (*nptr++ == 0)) count--;

  if (count != 0)
    return FALSE;
  else
    return TRUE;
}