#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* bc_num ;
struct TYPE_28__ {int n_scale; int* n_value; int n_len; } ;

/* Variables and functions */
 TYPE_1__* BCG (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int MAX (int,int) ; 
 int MIN (int,int) ; 
 int TRUE ; 
 int /*<<< orphan*/  _one_ ; 
 int /*<<< orphan*/  _zero_ ; 
 int /*<<< orphan*/  bc_add (TYPE_1__*,TYPE_1__*,TYPE_1__**,int /*<<< orphan*/ ) ; 
 int bc_compare (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* bc_copy_num (TYPE_1__*) ; 
 int /*<<< orphan*/  bc_divide (TYPE_1__*,TYPE_1__*,TYPE_1__**,int) ; 
 int /*<<< orphan*/  bc_free_num (TYPE_1__**) ; 
 int /*<<< orphan*/  bc_init_num (TYPE_1__**) ; 
 int /*<<< orphan*/  bc_int2num (TYPE_1__**,int) ; 
 scalar_t__ bc_is_near_zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bc_multiply (TYPE_1__*,TYPE_1__*,TYPE_1__**,int) ; 
 TYPE_1__* bc_new_num (int,int) ; 
 int /*<<< orphan*/  bc_raise (TYPE_1__*,TYPE_1__*,TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bc_sub (TYPE_1__*,TYPE_1__*,TYPE_1__**,int) ; 

int
bc_sqrt (bc_num *num, int scale)
{
  int rscale, cmp_res, done;
  int cscale;
  bc_num guess, guess1, point5, diff;

  /* Initial checks. */
  cmp_res = bc_compare (*num, BCG(_zero_));
  if (cmp_res < 0)
    return 0;		/* error */
  else
    {
      if (cmp_res == 0)
	{
	  bc_free_num (num);
	  *num = bc_copy_num (BCG(_zero_));
	  return 1;
	}
    }
  cmp_res = bc_compare (*num, BCG(_one_));
  if (cmp_res == 0)
    {
      bc_free_num (num);
      *num = bc_copy_num (BCG(_one_));
      return 1;
    }

  /* Initialize the variables. */
  rscale = MAX (scale, (*num)->n_scale);
  bc_init_num(&guess);
  bc_init_num(&guess1);
  bc_init_num(&diff);
  point5 = bc_new_num (1,1);
  point5->n_value[1] = 5;


  /* Calculate the initial guess. */
  if (cmp_res < 0)
    {
      /* The number is between 0 and 1.  Guess should start at 1. */
      guess = bc_copy_num (BCG(_one_));
      cscale = (*num)->n_scale;
    }
  else
    {
      /* The number is greater than 1.  Guess should start at 10^(exp/2). */
      bc_int2num (&guess,10);

      bc_int2num (&guess1,(*num)->n_len);
      bc_multiply (guess1, point5, &guess1, 0);
      guess1->n_scale = 0;
      bc_raise (guess, guess1, &guess, 0);
      bc_free_num (&guess1);
      cscale = 3;
    }

  /* Find the square root using Newton's algorithm. */
  done = FALSE;
  while (!done)
    {
      bc_free_num (&guess1);
      guess1 = bc_copy_num (guess);
      bc_divide (*num, guess, &guess, cscale);
      bc_add (guess, guess1, &guess, 0);
      bc_multiply (guess, point5, &guess, cscale);
      bc_sub (guess, guess1, &diff, cscale+1);
      if (bc_is_near_zero (diff, cscale))
	{
	  if (cscale < rscale+1)
	    cscale = MIN (cscale*3, rscale+1);
	  else
	    done = TRUE;
	}
    }

  /* Assign the number and clean up. */
  bc_free_num (num);
  bc_divide (guess,BCG(_one_),num,rscale);
  bc_free_num (&guess);
  bc_free_num (&guess1);
  bc_free_num (&point5);
  bc_free_num (&diff);
  return 1;
}