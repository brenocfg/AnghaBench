#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mpz_t ;
struct TYPE_4__ {int /*<<< orphan*/  mf; } ;
typedef  TYPE_1__ calc_number_t ;
struct TYPE_5__ {int size; } ;

/* Variables and functions */
#define  IDC_RADIO_BYTE 131 
#define  IDC_RADIO_DWORD 130 
#define  IDC_RADIO_QWORD 129 
#define  IDC_RADIO_WORD 128 
 int /*<<< orphan*/  MPFR_DEFAULT_RND ; 
 TYPE_2__ calc ; 
 int /*<<< orphan*/  mpfr_get_z (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_set_z (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_init_set_si (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpz_init_set_str (int /*<<< orphan*/ ,char*,int) ; 

void apply_int_mask(calc_number_t *r)
{
    mpz_t a, mask;

    switch (calc.size) {
    case IDC_RADIO_QWORD:
        mpz_init_set_str(mask, "FFFFFFFFFFFFFFFF", 16);
        break;
    case IDC_RADIO_DWORD:
        mpz_init_set_str(mask, "00000000FFFFFFFF", 16);
        break;
    case IDC_RADIO_WORD:
        mpz_init_set_str(mask, "000000000000FFFF", 16);
        break;
    case IDC_RADIO_BYTE:
        mpz_init_set_str(mask, "00000000000000FF", 16);
        break;
    default:
        mpz_init_set_si(mask, -1);
    }
    mpz_init(a);
    mpfr_get_z(a, r->mf, MPFR_DEFAULT_RND);
    mpz_and(a, a, mask);
    mpfr_set_z(r->mf, a, MPFR_DEFAULT_RND);
    mpz_clear(a);
    mpz_clear(mask);
}