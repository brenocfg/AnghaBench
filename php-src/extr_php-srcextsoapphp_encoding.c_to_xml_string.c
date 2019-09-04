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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlBufferPtr ;
typedef  int /*<<< orphan*/  encodeTypePtr ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_CAST (char*) ; 
 int /*<<< orphan*/  E_ERROR ; 
 int /*<<< orphan*/  FIND_ZVAL_NULL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_STRING ; 
 int SOAP_ENCODED ; 
 int /*<<< orphan*/ * SOAP_GLOBAL (int /*<<< orphan*/ ) ; 
 int ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* emalloc (int) ; 
 int /*<<< orphan*/  encoding ; 
 char* estrdup (char*) ; 
 char* estrndup (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  php_libxml_xmlCheckUTF8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ns_and_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soap_error1 (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  xmlAddChild (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xmlBufferContent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlBufferCreate () ; 
 int /*<<< orphan*/  xmlBufferCreateStatic (char*,int) ; 
 int /*<<< orphan*/  xmlBufferFree (int /*<<< orphan*/ ) ; 
 int xmlCharEncInFunc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlNewNode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlNewTextLen (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zval_get_string_func (int /*<<< orphan*/ *) ; 

__attribute__((used)) static xmlNodePtr to_xml_string(encodeTypePtr type, zval *data, int style, xmlNodePtr parent)
{
	xmlNodePtr ret, text;
	char *str;
	int new_len;

	ret = xmlNewNode(NULL, BAD_CAST("BOGUS"));
	xmlAddChild(parent, ret);
	FIND_ZVAL_NULL(data, ret, style);

	if (Z_TYPE_P(data) == IS_STRING) {
		str = estrndup(Z_STRVAL_P(data), Z_STRLEN_P(data));
		new_len = Z_STRLEN_P(data);
	} else {
		zend_string *tmp = zval_get_string_func(data);
		str = estrndup(ZSTR_VAL(tmp), ZSTR_LEN(tmp));
		new_len = ZSTR_LEN(tmp);
		zend_string_release_ex(tmp, 0);
	}

	if (SOAP_GLOBAL(encoding) != NULL) {
		xmlBufferPtr in  = xmlBufferCreateStatic(str, new_len);
		xmlBufferPtr out = xmlBufferCreate();
		int n = xmlCharEncInFunc(SOAP_GLOBAL(encoding), out, in);

		if (n >= 0) {
			efree(str);
			str = estrdup((char*)xmlBufferContent(out));
			new_len = n;
		}
		xmlBufferFree(out);
		xmlBufferFree(in);
	}

	if (!php_libxml_xmlCheckUTF8(BAD_CAST(str))) {
		char *err = emalloc(new_len + 8);
		char c;
		int i;

		memcpy(err, str, new_len+1);
		for (i = 0; (c = err[i++]);) {
			if ((c & 0x80) == 0) {
			} else if ((c & 0xe0) == 0xc0) {
				if ((err[i] & 0xc0) != 0x80) {
					break;
				}
				i++;
			} else if ((c & 0xf0) == 0xe0) {
				if ((err[i] & 0xc0) != 0x80 || (err[i+1] & 0xc0) != 0x80) {
					break;
				}
				i += 2;
			} else if ((c & 0xf8) == 0xf0) {
				if ((err[i] & 0xc0) != 0x80 || (err[i+1] & 0xc0) != 0x80 || (err[i+2] & 0xc0) != 0x80) {
					break;
				}
				i += 3;
			} else {
				break;
			}
		}
		if (c) {
			err[i-1] = '\\';
			err[i++] = 'x';
			err[i++] = ((unsigned char)c >> 4) + ((((unsigned char)c >> 4) > 9) ? ('a' - 10) : '0');
			err[i++] = (c & 15) + (((c & 15) > 9) ? ('a' - 10) : '0');
			err[i++] = '.';
			err[i++] = '.';
			err[i++] = '.';
			err[i++] = 0;
		}

		soap_error1(E_ERROR,  "Encoding: string '%s' is not a valid utf-8 string", err);
	}

	text = xmlNewTextLen(BAD_CAST(str), new_len);
	xmlAddChild(ret, text);
	efree(str);

	if (style == SOAP_ENCODED) {
		set_ns_and_type(ret, type);
	}
	return ret;
}