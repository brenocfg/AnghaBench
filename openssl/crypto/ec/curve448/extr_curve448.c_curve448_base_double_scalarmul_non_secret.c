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
struct smvt_control {int power; int addend; } ;
typedef  int /*<<< orphan*/  precmp_var ;
typedef  struct smvt_control pniels_t ;
typedef  int /*<<< orphan*/  curve448_scalar_t ;
typedef  int /*<<< orphan*/  curve448_point_t ;
typedef  int /*<<< orphan*/  control_var ;
typedef  int /*<<< orphan*/  control_pre ;

/* Variables and functions */
 int C448_SCALAR_BITS ; 
 int C448_WNAF_FIXED_TABLE_BITS ; 
 int C448_WNAF_VAR_TABLE_BITS ; 
 int /*<<< orphan*/  OPENSSL_cleanse (struct smvt_control*,int) ; 
 int /*<<< orphan*/  add_niels_to_pt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  add_pniels_to_pt (int /*<<< orphan*/ ,struct smvt_control,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  curve448_point_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curve448_point_identity ; 
 int /*<<< orphan*/ * curve448_wnaf_base ; 
 int /*<<< orphan*/  niels_to_pt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pniels_to_pt (int /*<<< orphan*/ ,struct smvt_control) ; 
 int /*<<< orphan*/  point_double_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prepare_wnaf_table (struct smvt_control*,int /*<<< orphan*/  const,int const) ; 
 int recode_wnaf (struct smvt_control*,int /*<<< orphan*/  const,int const) ; 
 int /*<<< orphan*/  sub_niels_from_pt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sub_pniels_from_pt (int /*<<< orphan*/ ,struct smvt_control,int) ; 

void curve448_base_double_scalarmul_non_secret(curve448_point_t combo,
                                               const curve448_scalar_t scalar1,
                                               const curve448_point_t base2,
                                               const curve448_scalar_t scalar2)
{
    const int table_bits_var = C448_WNAF_VAR_TABLE_BITS;
    const int table_bits_pre = C448_WNAF_FIXED_TABLE_BITS;
    struct smvt_control control_var[C448_SCALAR_BITS /
                                    (C448_WNAF_VAR_TABLE_BITS + 1) + 3];
    struct smvt_control control_pre[C448_SCALAR_BITS /
                                    (C448_WNAF_FIXED_TABLE_BITS + 1) + 3];
    int ncb_pre = recode_wnaf(control_pre, scalar1, table_bits_pre);
    int ncb_var = recode_wnaf(control_var, scalar2, table_bits_var);
    pniels_t precmp_var[1 << C448_WNAF_VAR_TABLE_BITS];
    int contp = 0, contv = 0, i;

    prepare_wnaf_table(precmp_var, base2, table_bits_var);
    i = control_var[0].power;

    if (i < 0) {
        curve448_point_copy(combo, curve448_point_identity);
        return;
    }
    if (i > control_pre[0].power) {
        pniels_to_pt(combo, precmp_var[control_var[0].addend >> 1]);
        contv++;
    } else if (i == control_pre[0].power && i >= 0) {
        pniels_to_pt(combo, precmp_var[control_var[0].addend >> 1]);
        add_niels_to_pt(combo, curve448_wnaf_base[control_pre[0].addend >> 1],
                        i);
        contv++;
        contp++;
    } else {
        i = control_pre[0].power;
        niels_to_pt(combo, curve448_wnaf_base[control_pre[0].addend >> 1]);
        contp++;
    }

    for (i--; i >= 0; i--) {
        int cv = (i == control_var[contv].power);
        int cp = (i == control_pre[contp].power);

        point_double_internal(combo, combo, i && !(cv || cp));

        if (cv) {
            assert(control_var[contv].addend);

            if (control_var[contv].addend > 0)
                add_pniels_to_pt(combo,
                                 precmp_var[control_var[contv].addend >> 1],
                                 i && !cp);
            else
                sub_pniels_from_pt(combo,
                                   precmp_var[(-control_var[contv].addend)
                                              >> 1], i && !cp);
            contv++;
        }

        if (cp) {
            assert(control_pre[contp].addend);

            if (control_pre[contp].addend > 0)
                add_niels_to_pt(combo,
                                curve448_wnaf_base[control_pre[contp].addend
                                                   >> 1], i);
            else
                sub_niels_from_pt(combo,
                                  curve448_wnaf_base[(-control_pre
                                                      [contp].addend) >> 1], i);
            contp++;
        }
    }

    /* This function is non-secret, but whatever this is cheap. */
    OPENSSL_cleanse(control_var, sizeof(control_var));
    OPENSSL_cleanse(control_pre, sizeof(control_pre));
    OPENSSL_cleanse(precmp_var, sizeof(precmp_var));

    assert(contv == ncb_var);
    (void)ncb_var;
    assert(contp == ncb_pre);
    (void)ncb_pre;
}