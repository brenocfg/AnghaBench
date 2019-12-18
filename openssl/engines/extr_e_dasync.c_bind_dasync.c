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
struct dasync_pipeline_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  SHA_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  BN_mod_exp_mont ; 
 int /*<<< orphan*/  DASYNC_F_BIND_DASYNC ; 
 int /*<<< orphan*/  DASYNC_R_INIT_FAILED ; 
 int /*<<< orphan*/  DASYNCerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_RSA (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_set_ciphers (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_destroy_function (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_digests (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_finish_function (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_init_function (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_load_DASYNC_strings () ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_CIPHER_meth_new (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_cleanup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_do_cipher (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_flags (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_impl_ctx_size (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_iv_length (int /*<<< orphan*/ *,int) ; 
 int EVP_CIPH_CBC_MODE ; 
 int EVP_CIPH_FLAG_AEAD_CIPHER ; 
 int EVP_CIPH_FLAG_DEFAULT_ASN1 ; 
 int EVP_CIPH_FLAG_PIPELINE ; 
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
 int /*<<< orphan*/  NID_aes_128_cbc ; 
 int /*<<< orphan*/  NID_aes_128_cbc_hmac_sha1 ; 
 int /*<<< orphan*/  NID_sha1 ; 
 int /*<<< orphan*/  NID_sha1WithRSAEncryption ; 
 int /*<<< orphan*/ * RSA_meth_new (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ RSA_meth_set_bn_mod_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RSA_meth_set_finish (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RSA_meth_set_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RSA_meth_set_mod_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RSA_meth_set_priv_dec (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RSA_meth_set_priv_enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RSA_meth_set_pub_dec (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RSA_meth_set_pub_enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHA_CBLOCK ; 
 int /*<<< orphan*/  SHA_DIGEST_LENGTH ; 
 int /*<<< orphan*/ * _hidden_aes_128_cbc ; 
 int /*<<< orphan*/ * _hidden_aes_128_cbc_hmac_sha1 ; 
 int /*<<< orphan*/ * _hidden_sha1_md ; 
 int /*<<< orphan*/  dasync_aes128_cbc_cipher ; 
 int /*<<< orphan*/  dasync_aes128_cbc_cleanup ; 
 int /*<<< orphan*/  dasync_aes128_cbc_ctrl ; 
 int /*<<< orphan*/  dasync_aes128_cbc_hmac_sha1_cipher ; 
 int /*<<< orphan*/  dasync_aes128_cbc_hmac_sha1_cleanup ; 
 int /*<<< orphan*/  dasync_aes128_cbc_hmac_sha1_ctrl ; 
 int /*<<< orphan*/  dasync_aes128_cbc_hmac_sha1_init_key ; 
 int /*<<< orphan*/  dasync_aes128_init_key ; 
 int /*<<< orphan*/  dasync_ciphers ; 
 int /*<<< orphan*/  dasync_destroy ; 
 int /*<<< orphan*/  dasync_digests ; 
 int /*<<< orphan*/  dasync_finish ; 
 int /*<<< orphan*/  dasync_init ; 
 int /*<<< orphan*/  dasync_pub_dec ; 
 int /*<<< orphan*/  dasync_pub_enc ; 
 int /*<<< orphan*/  dasync_rsa_finish ; 
 int /*<<< orphan*/  dasync_rsa_init ; 
 int /*<<< orphan*/ * dasync_rsa_method ; 
 int /*<<< orphan*/  dasync_rsa_mod_exp ; 
 int /*<<< orphan*/  dasync_rsa_priv_dec ; 
 int /*<<< orphan*/  dasync_rsa_priv_enc ; 
 int /*<<< orphan*/  dasync_sha1_final ; 
 int /*<<< orphan*/  dasync_sha1_init ; 
 int /*<<< orphan*/  dasync_sha1_update ; 
 int /*<<< orphan*/  engine_dasync_id ; 
 int /*<<< orphan*/  engine_dasync_name ; 

__attribute__((used)) static int bind_dasync(ENGINE *e)
{
    /* Setup RSA_METHOD */
    if ((dasync_rsa_method = RSA_meth_new("Dummy Async RSA method", 0)) == NULL
        || RSA_meth_set_pub_enc(dasync_rsa_method, dasync_pub_enc) == 0
        || RSA_meth_set_pub_dec(dasync_rsa_method, dasync_pub_dec) == 0
        || RSA_meth_set_priv_enc(dasync_rsa_method, dasync_rsa_priv_enc) == 0
        || RSA_meth_set_priv_dec(dasync_rsa_method, dasync_rsa_priv_dec) == 0
        || RSA_meth_set_mod_exp(dasync_rsa_method, dasync_rsa_mod_exp) == 0
        || RSA_meth_set_bn_mod_exp(dasync_rsa_method, BN_mod_exp_mont) == 0
        || RSA_meth_set_init(dasync_rsa_method, dasync_rsa_init) == 0
        || RSA_meth_set_finish(dasync_rsa_method, dasync_rsa_finish) == 0) {
        DASYNCerr(DASYNC_F_BIND_DASYNC, DASYNC_R_INIT_FAILED);
        return 0;
    }

    /* Ensure the dasync error handling is set up */
    ERR_load_DASYNC_strings();

    if (!ENGINE_set_id(e, engine_dasync_id)
        || !ENGINE_set_name(e, engine_dasync_name)
        || !ENGINE_set_RSA(e, dasync_rsa_method)
        || !ENGINE_set_digests(e, dasync_digests)
        || !ENGINE_set_ciphers(e, dasync_ciphers)
        || !ENGINE_set_destroy_function(e, dasync_destroy)
        || !ENGINE_set_init_function(e, dasync_init)
        || !ENGINE_set_finish_function(e, dasync_finish)) {
        DASYNCerr(DASYNC_F_BIND_DASYNC, DASYNC_R_INIT_FAILED);
        return 0;
    }

    /*
     * Set up the EVP_CIPHER and EVP_MD objects for the ciphers/digests
     * supplied by this engine
     */
    _hidden_sha1_md = EVP_MD_meth_new(NID_sha1, NID_sha1WithRSAEncryption);
    if (_hidden_sha1_md == NULL
        || !EVP_MD_meth_set_result_size(_hidden_sha1_md, SHA_DIGEST_LENGTH)
        || !EVP_MD_meth_set_input_blocksize(_hidden_sha1_md, SHA_CBLOCK)
        || !EVP_MD_meth_set_app_datasize(_hidden_sha1_md,
                                         sizeof(EVP_MD *) + sizeof(SHA_CTX))
        || !EVP_MD_meth_set_flags(_hidden_sha1_md, EVP_MD_FLAG_DIGALGID_ABSENT)
        || !EVP_MD_meth_set_init(_hidden_sha1_md, dasync_sha1_init)
        || !EVP_MD_meth_set_update(_hidden_sha1_md, dasync_sha1_update)
        || !EVP_MD_meth_set_final(_hidden_sha1_md, dasync_sha1_final)) {
        EVP_MD_meth_free(_hidden_sha1_md);
        _hidden_sha1_md = NULL;
    }

    _hidden_aes_128_cbc = EVP_CIPHER_meth_new(NID_aes_128_cbc,
                                              16 /* block size */,
                                              16 /* key len */);
    if (_hidden_aes_128_cbc == NULL
            || !EVP_CIPHER_meth_set_iv_length(_hidden_aes_128_cbc,16)
            || !EVP_CIPHER_meth_set_flags(_hidden_aes_128_cbc,
                                          EVP_CIPH_FLAG_DEFAULT_ASN1
                                          | EVP_CIPH_CBC_MODE
                                          | EVP_CIPH_FLAG_PIPELINE)
            || !EVP_CIPHER_meth_set_init(_hidden_aes_128_cbc,
                                         dasync_aes128_init_key)
            || !EVP_CIPHER_meth_set_do_cipher(_hidden_aes_128_cbc,
                                              dasync_aes128_cbc_cipher)
            || !EVP_CIPHER_meth_set_cleanup(_hidden_aes_128_cbc,
                                            dasync_aes128_cbc_cleanup)
            || !EVP_CIPHER_meth_set_ctrl(_hidden_aes_128_cbc,
                                         dasync_aes128_cbc_ctrl)
            || !EVP_CIPHER_meth_set_impl_ctx_size(_hidden_aes_128_cbc,
                                sizeof(struct dasync_pipeline_ctx))) {
        EVP_CIPHER_meth_free(_hidden_aes_128_cbc);
        _hidden_aes_128_cbc = NULL;
    }

    _hidden_aes_128_cbc_hmac_sha1 = EVP_CIPHER_meth_new(
                                                NID_aes_128_cbc_hmac_sha1,
                                                16 /* block size */,
                                                16 /* key len */);
    if (_hidden_aes_128_cbc_hmac_sha1 == NULL
            || !EVP_CIPHER_meth_set_iv_length(_hidden_aes_128_cbc_hmac_sha1,16)
            || !EVP_CIPHER_meth_set_flags(_hidden_aes_128_cbc_hmac_sha1,
                                            EVP_CIPH_CBC_MODE
                                          | EVP_CIPH_FLAG_DEFAULT_ASN1
                                          | EVP_CIPH_FLAG_AEAD_CIPHER
                                          | EVP_CIPH_FLAG_PIPELINE)
            || !EVP_CIPHER_meth_set_init(_hidden_aes_128_cbc_hmac_sha1,
                                         dasync_aes128_cbc_hmac_sha1_init_key)
            || !EVP_CIPHER_meth_set_do_cipher(_hidden_aes_128_cbc_hmac_sha1,
                                            dasync_aes128_cbc_hmac_sha1_cipher)
            || !EVP_CIPHER_meth_set_cleanup(_hidden_aes_128_cbc_hmac_sha1,
                                            dasync_aes128_cbc_hmac_sha1_cleanup)
            || !EVP_CIPHER_meth_set_ctrl(_hidden_aes_128_cbc_hmac_sha1,
                                         dasync_aes128_cbc_hmac_sha1_ctrl)
            || !EVP_CIPHER_meth_set_impl_ctx_size(_hidden_aes_128_cbc_hmac_sha1,
                                sizeof(struct dasync_pipeline_ctx))) {
        EVP_CIPHER_meth_free(_hidden_aes_128_cbc_hmac_sha1);
        _hidden_aes_128_cbc_hmac_sha1 = NULL;
    }

    return 1;
}