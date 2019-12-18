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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_long ;
struct php_x509_request {char* config_filename; char* section_name; char* digest_name; char* extensions_section; char* request_extensions_section; int priv_key_encrypt; int /*<<< orphan*/ * req_config; int /*<<< orphan*/  curve_name; int /*<<< orphan*/ * digest; int /*<<< orphan*/ * md_alg; int /*<<< orphan*/  const* priv_key_encrypt_cipher; int /*<<< orphan*/  priv_key_type; int /*<<< orphan*/  priv_key_bits; int /*<<< orphan*/ * global_config; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_set_default_mask_asc (char*) ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONF_get_number (int /*<<< orphan*/ *,char*,char*) ; 
 char* CONF_get_string (int /*<<< orphan*/ *,char*,char*) ; 
 void* CONF_load (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_get_digestbyname (char*) ; 
 int /*<<< orphan*/ * EVP_sha1 () ; 
 int /*<<< orphan*/  E_WARNING ; 
 int FAILURE ; 
 scalar_t__ IS_LONG ; 
 scalar_t__ IS_STRING ; 
 scalar_t__ IS_TRUE ; 
 int /*<<< orphan*/  NID_undef ; 
 int /*<<< orphan*/  OBJ_create_objects (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBJ_sn2nid (char*) ; 
 int /*<<< orphan*/  OPENSSL_KEYTYPE_DEFAULT ; 
 int /*<<< orphan*/  PHP_OPENSSL_BIO_MODE_R (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHP_SSL_CONFIG_SYNTAX_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKCS7_BINARY ; 
 int /*<<< orphan*/  SET_OPTIONAL_LONG_ARG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_OPTIONAL_STRING_ARG (char*,char*,char*) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_LVAL_P (int /*<<< orphan*/ *) ; 
 char* Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 char* default_ssl_conf_filename ; 
 int /*<<< orphan*/  extensions_section ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int php_openssl_add_oid_section (struct php_x509_request*) ; 
 int /*<<< orphan*/ * php_openssl_get_evp_cipher_from_algo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_openssl_open_base_dir_chk (char*) ; 
 int /*<<< orphan*/  php_openssl_store_errors () ; 
 int /*<<< orphan*/  request_extensions_section ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/ * zend_hash_str_find (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int php_openssl_parse_config(struct php_x509_request * req, zval * optional_args) /* {{{ */
{
	char * str;
	zval * item;

	SET_OPTIONAL_STRING_ARG("config", req->config_filename, default_ssl_conf_filename);
	SET_OPTIONAL_STRING_ARG("config_section_name", req->section_name, "req");
	req->global_config = CONF_load(NULL, default_ssl_conf_filename, NULL);
	if (req->global_config == NULL) {
		php_openssl_store_errors();
	}
	req->req_config = CONF_load(NULL, req->config_filename, NULL);
	if (req->req_config == NULL) {
		php_openssl_store_errors();
		return FAILURE;
	}

	/* read in the oids */
	str = CONF_get_string(req->req_config, NULL, "oid_file");
	if (str == NULL) {
		php_openssl_store_errors();
	} else if (!php_openssl_open_base_dir_chk(str)) {
		BIO *oid_bio = BIO_new_file(str, PHP_OPENSSL_BIO_MODE_R(PKCS7_BINARY));
		if (oid_bio) {
			OBJ_create_objects(oid_bio);
			BIO_free(oid_bio);
			php_openssl_store_errors();
		}
	}
	if (php_openssl_add_oid_section(req) == FAILURE) {
		return FAILURE;
	}
	SET_OPTIONAL_STRING_ARG("digest_alg", req->digest_name,
		CONF_get_string(req->req_config, req->section_name, "default_md"));
	SET_OPTIONAL_STRING_ARG("x509_extensions", req->extensions_section,
		CONF_get_string(req->req_config, req->section_name, "x509_extensions"));
	SET_OPTIONAL_STRING_ARG("req_extensions", req->request_extensions_section,
		CONF_get_string(req->req_config, req->section_name, "req_extensions"));
	SET_OPTIONAL_LONG_ARG("private_key_bits", req->priv_key_bits,
		CONF_get_number(req->req_config, req->section_name, "default_bits"));

	SET_OPTIONAL_LONG_ARG("private_key_type", req->priv_key_type, OPENSSL_KEYTYPE_DEFAULT);

	if (optional_args && (item = zend_hash_str_find(Z_ARRVAL_P(optional_args), "encrypt_key", sizeof("encrypt_key")-1)) != NULL) {
		req->priv_key_encrypt = Z_TYPE_P(item) == IS_TRUE ? 1 : 0;
	} else {
		str = CONF_get_string(req->req_config, req->section_name, "encrypt_rsa_key");
		if (str == NULL) {
			str = CONF_get_string(req->req_config, req->section_name, "encrypt_key");
			/* it is sure that there are some errrors as str was NULL for encrypt_rsa_key */
			php_openssl_store_errors();
		}
		if (str != NULL && strcmp(str, "no") == 0) {
			req->priv_key_encrypt = 0;
		} else {
			req->priv_key_encrypt = 1;
		}
	}

	if (req->priv_key_encrypt &&
		optional_args &&
		(item = zend_hash_str_find(Z_ARRVAL_P(optional_args), "encrypt_key_cipher", sizeof("encrypt_key_cipher")-1)) != NULL &&
		Z_TYPE_P(item) == IS_LONG
	) {
		zend_long cipher_algo = Z_LVAL_P(item);
		const EVP_CIPHER* cipher = php_openssl_get_evp_cipher_from_algo(cipher_algo);
		if (cipher == NULL) {
			php_error_docref(NULL, E_WARNING, "Unknown cipher algorithm for private key.");
			return FAILURE;
		} else {
			req->priv_key_encrypt_cipher = cipher;
		}
	} else {
		req->priv_key_encrypt_cipher = NULL;
	}

	/* digest alg */
	if (req->digest_name == NULL) {
		req->digest_name = CONF_get_string(req->req_config, req->section_name, "default_md");
	}
	if (req->digest_name != NULL) {
		req->digest = req->md_alg = EVP_get_digestbyname(req->digest_name);
	} else {
		php_openssl_store_errors();
	}
	if (req->md_alg == NULL) {
		req->md_alg = req->digest = EVP_sha1();
		php_openssl_store_errors();
	}

	PHP_SSL_CONFIG_SYNTAX_CHECK(extensions_section);
#ifdef HAVE_EVP_PKEY_EC
	/* set the ec group curve name */
	req->curve_name = NID_undef;
	if (optional_args && (item = zend_hash_str_find(Z_ARRVAL_P(optional_args), "curve_name", sizeof("curve_name")-1)) != NULL
		&& Z_TYPE_P(item) == IS_STRING) {
		req->curve_name = OBJ_sn2nid(Z_STRVAL_P(item));
		if (req->curve_name == NID_undef) {
			php_error_docref(NULL, E_WARNING, "Unknown elliptic curve (short) name %s", Z_STRVAL_P(item));
			return FAILURE;
		}
	}
#endif

	/* set the string mask */
	str = CONF_get_string(req->req_config, req->section_name, "string_mask");
	if (str == NULL) {
		php_openssl_store_errors();
	} else if (!ASN1_STRING_set_default_mask_asc(str)) {
		php_error_docref(NULL, E_WARNING, "Invalid global string mask setting %s", str);
		return FAILURE;
	}

	PHP_SSL_CONFIG_SYNTAX_CHECK(request_extensions_section);

	return SUCCESS;
}