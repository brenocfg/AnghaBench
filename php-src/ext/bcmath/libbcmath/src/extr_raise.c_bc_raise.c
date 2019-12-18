#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* bc_num ;
struct TYPE_16__ {scalar_t__ n_scale; int n_len; scalar_t__* n_value; } ;

/* Variables and functions */
 TYPE_1__* BCG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_WARNING ; 
 char FALSE ; 
 int /*<<< orphan*/  MAX (int,long) ; 
 int MIN (long,int /*<<< orphan*/ ) ; 
 char TRUE ; 
 int /*<<< orphan*/  _one_ ; 
 TYPE_1__* bc_copy_num (TYPE_1__*) ; 
 int /*<<< orphan*/  bc_divide (TYPE_1__*,TYPE_1__*,TYPE_1__**,int) ; 
 int /*<<< orphan*/  bc_free_num (TYPE_1__**) ; 
 int /*<<< orphan*/  bc_multiply (TYPE_1__*,TYPE_1__*,TYPE_1__**,int) ; 
 long bc_num2long (TYPE_1__*) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

void
bc_raise (bc_num num1, bc_num num2, bc_num *result, int scale)
{
   bc_num temp, power;
   long exponent;
   int rscale;
   int pwrscale;
   int calcscale;
   char neg;

   /* Check the exponent for scale digits and convert to a long. */
   if (num2->n_scale != 0)
     php_error_docref (NULL, E_WARNING, "non-zero scale in exponent");
   exponent = bc_num2long (num2);
   if (exponent == 0 && (num2->n_len > 1 || num2->n_value[0] != 0))
       php_error_docref (NULL, E_WARNING, "exponent too large");

   /* Special case if exponent is a zero. */
   if (exponent == 0)
     {
       bc_free_num (result);
       *result = bc_copy_num (BCG(_one_));
       return;
     }

   /* Other initializations. */
   if (exponent < 0)
     {
       neg = TRUE;
       exponent = -exponent;
       rscale = scale;
     }
   else
     {
       neg = FALSE;
       rscale = MIN (num1->n_scale*exponent, MAX(scale, num1->n_scale));
     }

   /* Set initial value of temp.  */
   power = bc_copy_num (num1);
   pwrscale = num1->n_scale;
   while ((exponent & 1) == 0)
     {
       pwrscale = 2*pwrscale;
       bc_multiply (power, power, &power, pwrscale);
       exponent = exponent >> 1;
     }
   temp = bc_copy_num (power);
   calcscale = pwrscale;
   exponent = exponent >> 1;

   /* Do the calculation. */
   while (exponent > 0)
     {
       pwrscale = 2*pwrscale;
       bc_multiply (power, power, &power, pwrscale);
       if ((exponent & 1) == 1) {
	 calcscale = pwrscale + calcscale;
	 bc_multiply (temp, power, &temp, calcscale);
       }
       exponent = exponent >> 1;
     }

   /* Assign the value. */
   if (neg)
     {
       bc_divide (BCG(_one_), temp, result, rscale);
       bc_free_num (&temp);
     }
   else
     {
       bc_free_num (result);
       *result = temp;
       if ((*result)->n_scale > rscale)
	 (*result)->n_scale = rscale;
     }
   bc_free_num (&power);
}