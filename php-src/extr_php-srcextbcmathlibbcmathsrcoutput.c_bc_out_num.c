#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {int digit; struct TYPE_25__* next; } ;
typedef  TYPE_1__ stk_rec ;
typedef  TYPE_2__* bc_num ;
struct TYPE_26__ {scalar_t__ n_sign; char* n_value; int n_len; int n_scale; } ;

/* Variables and functions */
 int BCD_CHAR (int /*<<< orphan*/ ) ; 
 TYPE_2__* BCG (int /*<<< orphan*/ ) ; 
 scalar_t__ MINUS ; 
 void* PLUS ; 
 int /*<<< orphan*/  _one_ ; 
 TYPE_2__* bc_copy_num (TYPE_2__*) ; 
 int /*<<< orphan*/  bc_divide (TYPE_2__*,TYPE_2__*,TYPE_2__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bc_free_num (TYPE_2__**) ; 
 int /*<<< orphan*/  bc_init_num (TYPE_2__**) ; 
 int /*<<< orphan*/  bc_int2num (TYPE_2__**,int) ; 
 scalar_t__ bc_is_zero (TYPE_2__*) ; 
 int /*<<< orphan*/  bc_modulo (TYPE_2__*,TYPE_2__*,TYPE_2__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bc_multiply (TYPE_2__*,TYPE_2__*,TYPE_2__**,int) ; 
 void* bc_num2long (TYPE_2__*) ; 
 int /*<<< orphan*/  bc_out_long (int,int,int,void (*) (int)) ; 
 int /*<<< orphan*/  bc_sub (TYPE_2__*,TYPE_2__*,TYPE_2__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (TYPE_1__*) ; 
 scalar_t__ emalloc (int) ; 
 int* ref_str ; 
 void stub1 (int) ; 
 void stub10 (int) ; 
 void stub2 (int) ; 
 void stub3 (int) ; 
 void stub4 (int) ; 
 void stub5 (int) ; 
 void stub6 (int) ; 
 void stub7 (int) ; 
 void stub8 (int) ; 
 void stub9 (int) ; 

void
#ifdef __STDC__
bc_out_num (bc_num num, int o_base, void (*out_char)(int), int leading_zero)
#else
bc_out_num (bc_num num, int o_base, void (*out_char)(), int leading_zero)
#endif
{
  char *nptr;
  int  index, fdigit, pre_space;
  stk_rec *digits, *temp;
  bc_num int_part, frac_part, base, cur_dig, t_num, max_o_digit;

  /* The negative sign if needed. */
  if (num->n_sign == MINUS) (*out_char) ('-');

  /* Output the number. */
  if (bc_is_zero (num))
    (*out_char) ('0');
  else
    if (o_base == 10)
      {
	/* The number is in base 10, do it the fast way. */
	nptr = num->n_value;
	if (num->n_len > 1 || *nptr != 0)
	  for (index=num->n_len; index>0; index--)
	    (*out_char) (BCD_CHAR(*nptr++));
	else
	  nptr++;

	if (leading_zero && bc_is_zero (num))
	  (*out_char) ('0');

	/* Now the fraction. */
	if (num->n_scale > 0)
	  {
	    (*out_char) ('.');
	    for (index=0; index<num->n_scale; index++)
	      (*out_char) (BCD_CHAR(*nptr++));
	  }
      }
    else
      {
	/* special case ... */
	if (leading_zero && bc_is_zero (num))
	  (*out_char) ('0');

	/* The number is some other base. */
	digits = NULL;
	bc_init_num (&int_part);
	bc_divide (num, BCG(_one_), &int_part, 0);
	bc_init_num (&frac_part);
	bc_init_num (&cur_dig);
	bc_init_num (&base);
	bc_sub (num, int_part, &frac_part, 0);
	/* Make the INT_PART and FRAC_PART positive. */
	int_part->n_sign = PLUS;
	frac_part->n_sign = PLUS;
	bc_int2num (&base, o_base);
	bc_init_num (&max_o_digit);
	bc_int2num (&max_o_digit, o_base-1);


	/* Get the digits of the integer part and push them on a stack. */
	while (!bc_is_zero (int_part))
	  {
	    bc_modulo (int_part, base, &cur_dig, 0);
		/* PHP Change:  malloc() -> emalloc() */
	    temp = (stk_rec *) emalloc (sizeof(stk_rec));
	    temp->digit = bc_num2long (cur_dig);
	    temp->next = digits;
	    digits = temp;
	    bc_divide (int_part, base, &int_part, 0);
	  }

	/* Print the digits on the stack. */
	if (digits != NULL)
	  {
	    /* Output the digits. */
	    while (digits != NULL)
	      {
		temp = digits;
		digits = digits->next;
		if (o_base <= 16)
		  (*out_char) (ref_str[ (int) temp->digit]);
		else
		  bc_out_long (temp->digit, max_o_digit->n_len, 1, out_char);
		efree (temp);
	      }
	  }

	/* Get and print the digits of the fraction part. */
	if (num->n_scale > 0)
	  {
	    (*out_char) ('.');
	    pre_space = 0;
	    t_num = bc_copy_num (BCG(_one_));
	    while (t_num->n_len <= num->n_scale) {
	      bc_multiply (frac_part, base, &frac_part, num->n_scale);
	      fdigit = bc_num2long (frac_part);
	      bc_int2num (&int_part, fdigit);
	      bc_sub (frac_part, int_part, &frac_part, 0);
	      if (o_base <= 16)
		(*out_char) (ref_str[fdigit]);
	      else {
		bc_out_long (fdigit, max_o_digit->n_len, pre_space, out_char);
		pre_space = 1;
	      }
	      bc_multiply (t_num, base, &t_num, 0);
	    }
	    bc_free_num (&t_num);
	  }

	/* Clean up. */
	bc_free_num (&int_part);
	bc_free_num (&frac_part);
	bc_free_num (&base);
	bc_free_num (&cur_dig);
	bc_free_num (&max_o_digit);
      }
}