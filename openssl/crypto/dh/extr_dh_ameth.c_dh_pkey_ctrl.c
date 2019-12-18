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
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
#define  ASN1_PKEY_CTRL_GET1_TLS_ENCPT 129 
#define  ASN1_PKEY_CTRL_SET1_TLS_ENCPT 128 
 int /*<<< orphan*/  EVP_PKEY_get0_DH (int /*<<< orphan*/ *) ; 
 int dh_buf2key (int /*<<< orphan*/ ,void*,long) ; 
 int dh_key2buf (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int dh_pkey_ctrl(EVP_PKEY *pkey, int op, long arg1, void *arg2)
{
    switch (op) {
    case ASN1_PKEY_CTRL_SET1_TLS_ENCPT:
        return dh_buf2key(EVP_PKEY_get0_DH(pkey), arg2, arg1);
    case ASN1_PKEY_CTRL_GET1_TLS_ENCPT:
        return dh_key2buf(EVP_PKEY_get0_DH(pkey), arg2);
    default:
        return -2;
    }
}