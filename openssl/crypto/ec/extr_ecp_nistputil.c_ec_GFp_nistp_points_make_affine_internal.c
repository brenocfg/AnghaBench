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

/* Variables and functions */
 void const* X (int) ; 
 void const* Y (int) ; 
 void* Z (int) ; 
 void const* tmp_felem (int) ; 

void ec_GFp_nistp_points_make_affine_internal(size_t num, void *point_array,
                                              size_t felem_size,
                                              void *tmp_felems,
                                              void (*felem_one) (void *out),
                                              int (*felem_is_zero) (const void
                                                                    *in),
                                              void (*felem_assign) (void *out,
                                                                    const void
                                                                    *in),
                                              void (*felem_square) (void *out,
                                                                    const void
                                                                    *in),
                                              void (*felem_mul) (void *out,
                                                                 const void
                                                                 *in1,
                                                                 const void
                                                                 *in2),
                                              void (*felem_inv) (void *out,
                                                                 const void
                                                                 *in),
                                              void (*felem_contract) (void
                                                                      *out,
                                                                      const
                                                                      void
                                                                      *in))
{
    int i = 0;

# define tmp_felem(I) (&((char *)tmp_felems)[(I) * felem_size])
# define X(I) (&((char *)point_array)[3*(I) * felem_size])
# define Y(I) (&((char *)point_array)[(3*(I) + 1) * felem_size])
# define Z(I) (&((char *)point_array)[(3*(I) + 2) * felem_size])

    if (!felem_is_zero(Z(0)))
        felem_assign(tmp_felem(0), Z(0));
    else
        felem_one(tmp_felem(0));
    for (i = 1; i < (int)num; i++) {
        if (!felem_is_zero(Z(i)))
            felem_mul(tmp_felem(i), tmp_felem(i - 1), Z(i));
        else
            felem_assign(tmp_felem(i), tmp_felem(i - 1));
    }
    /*
     * Now each tmp_felem(i) is the product of Z(0) .. Z(i), skipping any
     * zero-valued factors: if Z(i) = 0, we essentially pretend that Z(i) = 1
     */

    felem_inv(tmp_felem(num - 1), tmp_felem(num - 1));
    for (i = num - 1; i >= 0; i--) {
        if (i > 0)
            /*
             * tmp_felem(i-1) is the product of Z(0) .. Z(i-1), tmp_felem(i)
             * is the inverse of the product of Z(0) .. Z(i)
             */
            /* 1/Z(i) */
            felem_mul(tmp_felem(num), tmp_felem(i - 1), tmp_felem(i));
        else
            felem_assign(tmp_felem(num), tmp_felem(0)); /* 1/Z(0) */

        if (!felem_is_zero(Z(i))) {
            if (i > 0)
                /*
                 * For next iteration, replace tmp_felem(i-1) by its inverse
                 */
                felem_mul(tmp_felem(i - 1), tmp_felem(i), Z(i));

            /*
             * Convert point (X, Y, Z) into affine form (X/(Z^2), Y/(Z^3), 1)
             */
            felem_square(Z(i), tmp_felem(num)); /* 1/(Z^2) */
            felem_mul(X(i), X(i), Z(i)); /* X/(Z^2) */
            felem_mul(Z(i), Z(i), tmp_felem(num)); /* 1/(Z^3) */
            felem_mul(Y(i), Y(i), Z(i)); /* Y/(Z^3) */
            felem_contract(X(i), X(i));
            felem_contract(Y(i), Y(i));
            felem_one(Z(i));
        } else {
            if (i > 0)
                /*
                 * For next iteration, replace tmp_felem(i-1) by its inverse
                 */
                felem_assign(tmp_felem(i - 1), tmp_felem(i));
        }
    }
}