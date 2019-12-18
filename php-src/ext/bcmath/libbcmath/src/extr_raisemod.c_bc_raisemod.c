#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* bc_num ;
struct TYPE_27__ {scalar_t__ n_scale; } ;

/* Variables and functions */
 TYPE_1__* BCG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_WARNING ; 
 int MAX (int,scalar_t__) ; 
 int /*<<< orphan*/  _bc_truncate (TYPE_1__**) ; 
 int /*<<< orphan*/  _one_ ; 
 int /*<<< orphan*/  _two_ ; 
 int /*<<< orphan*/  bc_compare (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* bc_copy_num (TYPE_1__*) ; 
 int /*<<< orphan*/  bc_divmod (TYPE_1__*,TYPE_1__*,TYPE_1__**,TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bc_free_num (TYPE_1__**) ; 
 int /*<<< orphan*/  bc_init_num (TYPE_1__**) ; 
 scalar_t__ bc_is_neg (TYPE_1__*) ; 
 scalar_t__ bc_is_zero (TYPE_1__*) ; 
 int /*<<< orphan*/  bc_modulo (TYPE_1__*,TYPE_1__*,TYPE_1__**,int) ; 
 int /*<<< orphan*/  bc_multiply (TYPE_1__*,TYPE_1__*,TYPE_1__**,int) ; 
 TYPE_1__* bc_new_num (int,int) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

int
bc_raisemod (bc_num base, bc_num expo, bc_num mod, bc_num *result, int scale)
{
  bc_num power, exponent, modulus, parity, temp;
  int rscale;

  /* Check for correct numbers. */
  if (bc_is_zero(mod)) return -1;
  if (bc_is_neg(expo)) return -1;

  /* Set initial values.  */
  power = bc_copy_num (base);
  exponent = bc_copy_num (expo);
  modulus = bc_copy_num (mod);
  temp = bc_copy_num (BCG(_one_));
  bc_init_num(&parity);

  /* Check the base for scale digits. */
  if (power->n_scale != 0)
    {
      php_error_docref (NULL, E_WARNING, "non-zero scale in base");
      _bc_truncate (&power);
    }

  /* Check the exponent for scale digits. */
  if (exponent->n_scale != 0)
    {
      php_error_docref (NULL, E_WARNING, "non-zero scale in exponent");
      _bc_truncate (&exponent);
    }

  /* Check the modulus for scale digits. */
  if (modulus->n_scale != 0)
    {
      php_error_docref (NULL, E_WARNING, "non-zero scale in modulus");
      _bc_truncate (&modulus);
    }

  /* Do the calculation. */
  rscale = MAX(scale, power->n_scale);
  if ( !bc_compare(modulus, BCG(_one_)) )
    {
      bc_free_num (&temp);
      temp = bc_new_num (1, scale);
    }
  else
    {
      while ( !bc_is_zero(exponent) )
	{
	  (void) bc_divmod (exponent, BCG(_two_), &exponent, &parity, 0);
	  if ( !bc_is_zero(parity) )
	    {
	      bc_multiply (temp, power, &temp, rscale);
	      (void) bc_modulo (temp, modulus, &temp, scale);
	    }

	  bc_multiply (power, power, &power, rscale);
	  (void) bc_modulo (power, modulus, &power, scale);
	}
    }

  /* Assign the value. */
  bc_free_num (&power);
  bc_free_num (&exponent);
  bc_free_num (&modulus);
  bc_free_num (result);
  bc_free_num (&parity);
  *result = temp;
  return 0;	/* Everything is OK. */
}