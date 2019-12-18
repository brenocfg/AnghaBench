#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int key_bits; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 int EVP_CIPHER_CTX_key_length (int /*<<< orphan*/ *) ; 
#define  EVP_CTRL_GET_RC2_KEY_BITS 131 
#define  EVP_CTRL_INIT 130 
#define  EVP_CTRL_PBE_PRF_NID 129 
#define  EVP_CTRL_SET_RC2_KEY_BITS 128 
 int NID_hmacWithMD5 ; 
 TYPE_1__* data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rc2_ctrl(EVP_CIPHER_CTX *c, int type, int arg, void *ptr)
{
    switch (type) {
    case EVP_CTRL_INIT:
        data(c)->key_bits = EVP_CIPHER_CTX_key_length(c) * 8;
        return 1;

    case EVP_CTRL_GET_RC2_KEY_BITS:
        *(int *)ptr = data(c)->key_bits;
        return 1;

    case EVP_CTRL_SET_RC2_KEY_BITS:
        if (arg > 0) {
            data(c)->key_bits = arg;
            return 1;
        }
        return 0;
# ifdef PBE_PRF_TEST
    case EVP_CTRL_PBE_PRF_NID:
        *(int *)ptr = NID_hmacWithMD5;
        return 1;
# endif

    default:
        return -1;
    }
}