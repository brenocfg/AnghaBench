#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * cbc128_f ;
typedef  void* block128_f ;
struct TYPE_6__ {int /*<<< orphan*/  ks; } ;
struct TYPE_9__ {TYPE_1__ ks; } ;
struct TYPE_7__ {int /*<<< orphan*/ * cbc; } ;
struct TYPE_8__ {int mode; TYPE_2__ stream; void* block; scalar_t__ enc; int /*<<< orphan*/ * ks; } ;
typedef  TYPE_3__ PROV_CIPHER_CTX ;
typedef  TYPE_4__ PROV_CAMELLIA_CTX ;
typedef  int /*<<< orphan*/  CAMELLIA_KEY ;

/* Variables and functions */
 scalar_t__ Camellia_cbc_encrypt ; 
 scalar_t__ Camellia_decrypt ; 
 scalar_t__ Camellia_encrypt ; 
 int Camellia_set_key (unsigned char const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EVP_CIPH_CBC_MODE ; 
 int EVP_CIPH_ECB_MODE ; 
 int /*<<< orphan*/  EVP_R_ARIA_KEY_SETUP_FAILED ; 

__attribute__((used)) static int cipher_hw_camellia_initkey(PROV_CIPHER_CTX *dat,
                                      const unsigned char *key, size_t keylen)
{
    int ret, mode = dat->mode;
    PROV_CAMELLIA_CTX *adat = (PROV_CAMELLIA_CTX *)dat;
    CAMELLIA_KEY *ks = &adat->ks.ks;

    dat->ks = ks;
    ret = Camellia_set_key(key, keylen * 8, ks);
    if (ret < 0) {
        ERR_raise(ERR_LIB_PROV, EVP_R_ARIA_KEY_SETUP_FAILED);
        return 0;
    }
    if (dat->enc || (mode != EVP_CIPH_ECB_MODE && mode != EVP_CIPH_CBC_MODE)) {
        dat->block = (block128_f) Camellia_encrypt;
        dat->stream.cbc = mode == EVP_CIPH_CBC_MODE ?
            (cbc128_f) Camellia_cbc_encrypt : NULL;
    } else {
        dat->block = (block128_f) Camellia_decrypt;
        dat->stream.cbc = mode == EVP_CIPH_CBC_MODE ?
            (cbc128_f) Camellia_cbc_encrypt : NULL;
    }
    return 1;
}