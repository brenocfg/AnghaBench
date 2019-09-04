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
typedef  int /*<<< orphan*/  X509_NAME_ENTRY ;
typedef  int /*<<< orphan*/  X509_NAME ;
typedef  int /*<<< orphan*/  ASN1_STRING ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 unsigned char* ASN1_STRING_get0_data (int /*<<< orphan*/ *) ; 
 int ASN1_STRING_length (int /*<<< orphan*/ *) ; 
 int ASN1_STRING_to_UTF8 (unsigned char**,int /*<<< orphan*/ *) ; 
 scalar_t__ ASN1_STRING_type (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ARRAY ; 
 scalar_t__ IS_STRING ; 
 scalar_t__ OBJ_nid2ln (int) ; 
 scalar_t__ OBJ_nid2sn (int) ; 
 int OBJ_obj2nid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 scalar_t__ V_ASN1_UTF8STRING ; 
 int /*<<< orphan*/ * X509_NAME_ENTRY_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_NAME_ENTRY_get_object (int /*<<< orphan*/ *) ; 
 int X509_NAME_entry_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_NAME_get_entry (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ZVAL_COPY_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ARRVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STR_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_assoc_stringl (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  add_next_index_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_next_index_stringl (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_openssl_store_errors () ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/ * zend_hash_str_find (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_str_update (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_copy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void php_openssl_add_assoc_name_entry(zval * val, char * key, X509_NAME * name, int shortname) /* {{{ */
{
	zval *data;
	zval subitem, tmp;
	int i;
	char *sname;
	int nid;
	X509_NAME_ENTRY * ne;
	ASN1_STRING * str = NULL;
	ASN1_OBJECT * obj;

	if (key != NULL) {
		array_init(&subitem);
	} else {
		ZVAL_COPY_VALUE(&subitem, val);
	}

	for (i = 0; i < X509_NAME_entry_count(name); i++) {
		const unsigned char *to_add = NULL;
		int to_add_len = 0;
		unsigned char *to_add_buf = NULL;

		ne = X509_NAME_get_entry(name, i);
		obj = X509_NAME_ENTRY_get_object(ne);
		nid = OBJ_obj2nid(obj);

		if (shortname) {
			sname = (char *) OBJ_nid2sn(nid);
		} else {
			sname = (char *) OBJ_nid2ln(nid);
		}

		str = X509_NAME_ENTRY_get_data(ne);
		if (ASN1_STRING_type(str) != V_ASN1_UTF8STRING) {
			/* ASN1_STRING_to_UTF8(3): The converted data is copied into a newly allocated buffer */
			to_add_len = ASN1_STRING_to_UTF8(&to_add_buf, str);
			to_add = to_add_buf;
		} else {
			/* ASN1_STRING_get0_data(3): Since this is an internal pointer it should not be freed or modified in any way */
			to_add = ASN1_STRING_get0_data(str);
			to_add_len = ASN1_STRING_length(str);
		}

		if (to_add_len != -1) {
			if ((data = zend_hash_str_find(Z_ARRVAL(subitem), sname, strlen(sname))) != NULL) {
				if (Z_TYPE_P(data) == IS_ARRAY) {
					add_next_index_stringl(data, (const char *)to_add, to_add_len);
				} else if (Z_TYPE_P(data) == IS_STRING) {
					array_init(&tmp);
					add_next_index_str(&tmp, zend_string_copy(Z_STR_P(data)));
					add_next_index_stringl(&tmp, (const char *)to_add, to_add_len);
					zend_hash_str_update(Z_ARRVAL(subitem), sname, strlen(sname), &tmp);
				}
			} else {
				/* it might be better to expand it and pass zval from ZVAL_STRING
				 * to zend_symtable_str_update so we do not silently drop const
				 * but we need a test to cover this part first */
				add_assoc_stringl(&subitem, sname, (char *)to_add, to_add_len);
			}
		} else {
			php_openssl_store_errors();
		}

		if (to_add_buf != NULL) {
			OPENSSL_free(to_add_buf);
		}
	}

	if (key != NULL) {
		zend_hash_str_update(Z_ARRVAL_P(val), key, strlen(key), &subitem);
	}
}