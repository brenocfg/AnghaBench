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
struct TYPE_4__ {int /*<<< orphan*/  pkey_check; int /*<<< orphan*/  siginf_set; int /*<<< orphan*/  item_verify; int /*<<< orphan*/  item_sign; int /*<<< orphan*/  pkey_ctrl; int /*<<< orphan*/  pkey_free; int /*<<< orphan*/  param_print; int /*<<< orphan*/  param_cmp; int /*<<< orphan*/  param_copy; int /*<<< orphan*/  param_missing; int /*<<< orphan*/  param_encode; int /*<<< orphan*/  param_decode; int /*<<< orphan*/  pkey_bits; int /*<<< orphan*/  pkey_size; int /*<<< orphan*/  old_priv_decode; int /*<<< orphan*/  old_priv_encode; int /*<<< orphan*/  priv_print; int /*<<< orphan*/  priv_encode; int /*<<< orphan*/  priv_decode; int /*<<< orphan*/  pub_print; int /*<<< orphan*/  pub_cmp; int /*<<< orphan*/  pub_encode; int /*<<< orphan*/  pub_decode; } ;
typedef  TYPE_1__ EVP_PKEY_ASN1_METHOD ;

/* Variables and functions */

void EVP_PKEY_asn1_copy(EVP_PKEY_ASN1_METHOD *dst,
                        const EVP_PKEY_ASN1_METHOD *src)
{

    dst->pub_decode = src->pub_decode;
    dst->pub_encode = src->pub_encode;
    dst->pub_cmp = src->pub_cmp;
    dst->pub_print = src->pub_print;

    dst->priv_decode = src->priv_decode;
    dst->priv_encode = src->priv_encode;
    dst->priv_print = src->priv_print;

    dst->old_priv_encode = src->old_priv_encode;
    dst->old_priv_decode = src->old_priv_decode;

    dst->pkey_size = src->pkey_size;
    dst->pkey_bits = src->pkey_bits;

    dst->param_decode = src->param_decode;
    dst->param_encode = src->param_encode;
    dst->param_missing = src->param_missing;
    dst->param_copy = src->param_copy;
    dst->param_cmp = src->param_cmp;
    dst->param_print = src->param_print;

    dst->pkey_free = src->pkey_free;
    dst->pkey_ctrl = src->pkey_ctrl;

    dst->item_sign = src->item_sign;
    dst->item_verify = src->item_verify;

    dst->siginf_set = src->siginf_set;

    dst->pkey_check = src->pkey_check;

}