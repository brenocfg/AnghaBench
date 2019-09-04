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
typedef  int /*<<< orphan*/  SHA_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MD_meth_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_meth_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_meth_set_app_datasize (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EVP_MD_meth_set_final (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_meth_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_meth_set_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_meth_set_input_blocksize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_meth_set_result_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_meth_set_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NID_sha1 ; 
 int /*<<< orphan*/  NID_sha1WithRSAEncryption ; 
 int /*<<< orphan*/  SHA_CBLOCK ; 
 int /*<<< orphan*/  SHA_DIGEST_LENGTH ; 
 int /*<<< orphan*/  const* sha1_md ; 
 int /*<<< orphan*/  test_sha1_final ; 
 int /*<<< orphan*/  test_sha1_init ; 
 int /*<<< orphan*/  test_sha1_update ; 

__attribute__((used)) static const EVP_MD *test_sha_md(void)
{
    if (sha1_md == NULL) {
        EVP_MD *md;

        if ((md = EVP_MD_meth_new(NID_sha1, NID_sha1WithRSAEncryption)) == NULL
            || !EVP_MD_meth_set_result_size(md, SHA_DIGEST_LENGTH)
            || !EVP_MD_meth_set_input_blocksize(md, SHA_CBLOCK)
            || !EVP_MD_meth_set_app_datasize(md,
                                             sizeof(EVP_MD *) + sizeof(SHA_CTX))
            || !EVP_MD_meth_set_flags(md, 0)
            || !EVP_MD_meth_set_init(md, test_sha1_init)
            || !EVP_MD_meth_set_update(md, test_sha1_update)
            || !EVP_MD_meth_set_final(md, test_sha1_final)) {
            EVP_MD_meth_free(md);
            md = NULL;
        }
        sha1_md = md;
    }
    return sha1_md;
}