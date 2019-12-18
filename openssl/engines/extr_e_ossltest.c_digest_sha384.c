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
typedef  int /*<<< orphan*/  SHA512_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MD_FLAG_DIGALGID_ABSENT ; 
 int /*<<< orphan*/  EVP_MD_meth_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_meth_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_meth_set_app_datasize (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EVP_MD_meth_set_final (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_meth_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_meth_set_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_meth_set_input_blocksize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_meth_set_result_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_meth_set_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NID_sha384 ; 
 int /*<<< orphan*/  NID_sha384WithRSAEncryption ; 
 int /*<<< orphan*/  SHA384_DIGEST_LENGTH ; 
 int /*<<< orphan*/  SHA512_CBLOCK ; 
 int /*<<< orphan*/  const* _hidden_sha384_md ; 
 int /*<<< orphan*/  digest_sha384_final ; 
 int /*<<< orphan*/  digest_sha384_init ; 
 int /*<<< orphan*/  digest_sha512_update ; 

__attribute__((used)) static const EVP_MD *digest_sha384(void)
{
    if (_hidden_sha384_md == NULL) {
        EVP_MD *md;

        if ((md = EVP_MD_meth_new(NID_sha384, NID_sha384WithRSAEncryption)) == NULL
            || !EVP_MD_meth_set_result_size(md, SHA384_DIGEST_LENGTH)
            || !EVP_MD_meth_set_input_blocksize(md, SHA512_CBLOCK)
            || !EVP_MD_meth_set_app_datasize(md,
                                             sizeof(EVP_MD *) + sizeof(SHA512_CTX))
            || !EVP_MD_meth_set_flags(md, EVP_MD_FLAG_DIGALGID_ABSENT)
            || !EVP_MD_meth_set_init(md, digest_sha384_init)
            || !EVP_MD_meth_set_update(md, digest_sha512_update)
            || !EVP_MD_meth_set_final(md, digest_sha384_final)) {
            EVP_MD_meth_free(md);
            md = NULL;
        }
        _hidden_sha384_md = md;
    }
    return _hidden_sha384_md;
}