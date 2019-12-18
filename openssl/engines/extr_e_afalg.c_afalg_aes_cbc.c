#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  const* _hidden; int /*<<< orphan*/  key_size; } ;
typedef  TYPE_1__ cbc_handles ;
typedef  int /*<<< orphan*/  afalg_ctx ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  AES_IV_LEN ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* EVP_CIPHER_meth_new (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_cleanup (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_do_cipher (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_flags (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_impl_ctx_size (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_init (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_iv_length (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int EVP_CIPH_CBC_MODE ; 
 int EVP_CIPH_FLAG_DEFAULT_ASN1 ; 
 int /*<<< orphan*/  afalg_cipher_cleanup ; 
 int /*<<< orphan*/  afalg_cipher_init ; 
 int /*<<< orphan*/  afalg_do_cipher ; 
 TYPE_1__* get_cipher_handle (int) ; 

__attribute__((used)) static const EVP_CIPHER *afalg_aes_cbc(int nid)
{
    cbc_handles *cipher_handle = get_cipher_handle(nid);
    if (cipher_handle->_hidden == NULL
        && ((cipher_handle->_hidden =
         EVP_CIPHER_meth_new(nid,
                             AES_BLOCK_SIZE,
                             cipher_handle->key_size)) == NULL
        || !EVP_CIPHER_meth_set_iv_length(cipher_handle->_hidden,
                                          AES_IV_LEN)
        || !EVP_CIPHER_meth_set_flags(cipher_handle->_hidden,
                                      EVP_CIPH_CBC_MODE |
                                      EVP_CIPH_FLAG_DEFAULT_ASN1)
        || !EVP_CIPHER_meth_set_init(cipher_handle->_hidden,
                                     afalg_cipher_init)
        || !EVP_CIPHER_meth_set_do_cipher(cipher_handle->_hidden,
                                          afalg_do_cipher)
        || !EVP_CIPHER_meth_set_cleanup(cipher_handle->_hidden,
                                        afalg_cipher_cleanup)
        || !EVP_CIPHER_meth_set_impl_ctx_size(cipher_handle->_hidden,
                                              sizeof(afalg_ctx)))) {
        EVP_CIPHER_meth_free(cipher_handle->_hidden);
        cipher_handle->_hidden= NULL;
    }
    return cipher_handle->_hidden;
}