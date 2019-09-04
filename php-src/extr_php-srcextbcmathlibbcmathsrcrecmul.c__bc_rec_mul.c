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
struct TYPE_20__ {int n_len; scalar_t__ n_sign; scalar_t__ n_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCG (int /*<<< orphan*/ ) ; 
 int MAX (int,int) ; 
 int MUL_SMALL_DIGITS ; 
 int /*<<< orphan*/  _bc_rm_leading_zeros (TYPE_1__*) ; 
 int /*<<< orphan*/  _bc_shift_addsub (TYPE_1__*,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  _bc_simp_mul (TYPE_1__*,int,TYPE_1__*,int,TYPE_1__**,int) ; 
 int /*<<< orphan*/  _zero_ ; 
 TYPE_1__* bc_copy_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bc_free_num (TYPE_1__**) ; 
 int /*<<< orphan*/  bc_init_num (TYPE_1__**) ; 
 scalar_t__ bc_is_zero (TYPE_1__*) ; 
 TYPE_1__* bc_new_num (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bc_sub (TYPE_1__*,TYPE_1__*,TYPE_1__**,int /*<<< orphan*/ ) ; 
 int mul_base_digits ; 
 TYPE_1__* new_sub_num (int,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
_bc_rec_mul (bc_num u, int ulen, bc_num v, int vlen, bc_num *prod,
	     int full_scale)
{
  bc_num u0, u1, v0, v1;
  bc_num m1, m2, m3, d1, d2;
  int n, prodlen, m1zero;
  int d1len, d2len;

  /* Base case? */
  if ((ulen+vlen) < mul_base_digits
      || ulen < MUL_SMALL_DIGITS
      || vlen < MUL_SMALL_DIGITS ) {
    _bc_simp_mul (u, ulen, v, vlen, prod, full_scale);
    return;
  }

  /* Calculate n -- the u and v split point in digits. */
  n = (MAX(ulen, vlen)+1) / 2;

  /* Split u and v. */
  if (ulen < n) {
    u1 = bc_copy_num (BCG(_zero_));
    u0 = new_sub_num (ulen,0, u->n_value);
  } else {
    u1 = new_sub_num (ulen-n, 0, u->n_value);
    u0 = new_sub_num (n, 0, u->n_value+ulen-n);
  }
  if (vlen < n) {
    v1 = bc_copy_num (BCG(_zero_));
    v0 = new_sub_num (vlen,0, v->n_value);
  } else {
    v1 = new_sub_num (vlen-n, 0, v->n_value);
    v0 = new_sub_num (n, 0, v->n_value+vlen-n);
    }
  _bc_rm_leading_zeros (u1);
  _bc_rm_leading_zeros (u0);
  _bc_rm_leading_zeros (v1);
  _bc_rm_leading_zeros (v0);

  m1zero = bc_is_zero(u1) || bc_is_zero(v1);

  /* Calculate sub results ... */

  bc_init_num(&d1);
  bc_init_num(&d2);
  bc_sub (u1, u0, &d1, 0);
  d1len = d1->n_len;
  bc_sub (v0, v1, &d2, 0);
  d2len = d2->n_len;


  /* Do recursive multiplies and shifted adds. */
  if (m1zero)
    m1 = bc_copy_num (BCG(_zero_));
  else
    _bc_rec_mul (u1, u1->n_len, v1, v1->n_len, &m1, 0);

  if (bc_is_zero(d1) || bc_is_zero(d2))
    m2 = bc_copy_num (BCG(_zero_));
  else
    _bc_rec_mul (d1, d1len, d2, d2len, &m2, 0);

  if (bc_is_zero(u0) || bc_is_zero(v0))
    m3 = bc_copy_num (BCG(_zero_));
  else
    _bc_rec_mul (u0, u0->n_len, v0, v0->n_len, &m3, 0);

  /* Initialize product */
  prodlen = ulen+vlen+1;
  *prod = bc_new_num(prodlen, 0);

  if (!m1zero) {
    _bc_shift_addsub (*prod, m1, 2*n, 0);
    _bc_shift_addsub (*prod, m1, n, 0);
  }
  _bc_shift_addsub (*prod, m3, n, 0);
  _bc_shift_addsub (*prod, m3, 0, 0);
  _bc_shift_addsub (*prod, m2, n, d1->n_sign != d2->n_sign);

  /* Now clean up! */
  bc_free_num (&u1);
  bc_free_num (&u0);
  bc_free_num (&v1);
  bc_free_num (&m1);
  bc_free_num (&v0);
  bc_free_num (&m2);
  bc_free_num (&m3);
  bc_free_num (&d1);
  bc_free_num (&d2);
}