#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* bc_num ;
struct TYPE_20__ {scalar_t__ n_scale; } ;

/* Variables and functions */
 int MAX (scalar_t__,scalar_t__) ; 
 TYPE_1__* bc_copy_num (TYPE_1__*) ; 
 int /*<<< orphan*/  bc_divide (TYPE_1__*,TYPE_1__*,TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bc_free_num (TYPE_1__**) ; 
 int /*<<< orphan*/  bc_init_num (TYPE_1__**) ; 
 scalar_t__ bc_is_zero (TYPE_1__*) ; 
 int /*<<< orphan*/  bc_multiply (TYPE_1__*,TYPE_1__*,TYPE_1__**,int) ; 
 int /*<<< orphan*/  bc_sub (TYPE_1__*,TYPE_1__*,TYPE_1__**,int) ; 

int
bc_divmod (bc_num num1, bc_num num2, bc_num *quot, bc_num *rem, int scale)
{
  bc_num quotient = NULL;
  bc_num temp;
  int rscale;

  /* Check for correct numbers. */
  if (bc_is_zero (num2)) return -1;

  /* Calculate final scale. */
  rscale = MAX (num1->n_scale, num2->n_scale+scale);
  bc_init_num(&temp);

  /* Calculate it. */
  bc_divide (num1, num2, &temp, 0);
  if (quot)
    quotient = bc_copy_num (temp);
  bc_multiply (temp, num2, &temp, rscale);
  bc_sub (num1, temp, rem, rscale);
  bc_free_num (&temp);

  if (quot)
    {
      bc_free_num (quot);
      *quot = quotient;
    }

  return 0;	/* Everything is OK. */
}