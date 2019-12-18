#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/ * xmlNodePtr ;
typedef  TYPE_1__* sdlTypePtr ;
typedef  TYPE_2__* encodeTypePtr ;
struct TYPE_12__ {int /*<<< orphan*/  type; TYPE_1__* sdl_type; } ;
struct TYPE_13__ {TYPE_2__ details; } ;
struct TYPE_11__ {int kind; TYPE_9__* encode; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_ERROR ; 
 int /*<<< orphan*/  IS_ARRAY ; 
 int SOAP_ENCODED ; 
 int /*<<< orphan*/  SOAP_ENC_ARRAY ; 
#define  XSD_TYPEKIND_COMPLEX 133 
#define  XSD_TYPEKIND_EXTENSION 132 
#define  XSD_TYPEKIND_LIST 131 
#define  XSD_TYPEKIND_RESTRICTION 130 
#define  XSD_TYPEKIND_SIMPLE 129 
#define  XSD_TYPEKIND_UNION 128 
 int /*<<< orphan*/ * guess_xml_convert (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * master_to_xml (TYPE_9__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_ns_and_type (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  soap_error0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * to_xml_array (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * to_xml_list (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * to_xml_object (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * to_xml_union (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

xmlNodePtr sdl_guess_convert_xml(encodeTypePtr enc, zval *data, int style, xmlNodePtr parent)
{
	sdlTypePtr type;
	xmlNodePtr ret = NULL;

	type = enc->sdl_type;

	if (type == NULL) {
		ret = guess_xml_convert(enc, data, style, parent);
		if (style == SOAP_ENCODED) {
			set_ns_and_type(ret, enc);
		}
		return ret;
	}
/*FIXME: restriction support
	if (type) {
		if (type->restrictions && Z_TYPE_P(data) == IS_STRING) {
			if (type->restrictions->enumeration) {
				if (!zend_hash_exists(type->restrictions->enumeration,Z_STRVAL_P(data),Z_STRLEN_P(data)+1)) {
					soap_error1(E_WARNING, "Encoding: Restriction: invalid enumeration value \"%s\".", Z_STRVAL_P(data));
				}
			}
			if (type->restrictions->minLength &&
			    Z_STRLEN_P(data) < type->restrictions->minLength->value) {
		  	soap_error0(E_WARNING, "Encoding: Restriction: length less than 'minLength'");
			}
			if (type->restrictions->maxLength &&
			    Z_STRLEN_P(data) > type->restrictions->maxLength->value) {
		  	soap_error0(E_WARNING, "Encoding: Restriction: length greater than 'maxLength'");
			}
			if (type->restrictions->length &&
			    Z_STRLEN_P(data) != type->restrictions->length->value) {
		  	soap_error0(E_WARNING, "Encoding: Restriction: length is not equal to 'length'");
			}
		}
	}
*/
	switch(type->kind) {
		case XSD_TYPEKIND_SIMPLE:
			if (type->encode && enc != &type->encode->details) {
				ret = master_to_xml(type->encode, data, style, parent);
			} else {
				ret = guess_xml_convert(enc, data, style, parent);
			}
			break;
		case XSD_TYPEKIND_LIST:
			ret = to_xml_list(enc, data, style, parent);
			break;
		case XSD_TYPEKIND_UNION:
			ret = to_xml_union(enc, data, style, parent);
			break;
		case XSD_TYPEKIND_COMPLEX:
		case XSD_TYPEKIND_RESTRICTION:
		case XSD_TYPEKIND_EXTENSION:
			if (type->encode &&
			    (type->encode->details.type == IS_ARRAY ||
			     type->encode->details.type == SOAP_ENC_ARRAY)) {
				return to_xml_array(enc, data, style, parent);
			} else {
				return to_xml_object(enc, data, style, parent);
			}
			break;
		default:
	  	soap_error0(E_ERROR, "Encoding: Internal Error");
			break;
	}
	if (style == SOAP_ENCODED) {
		set_ns_and_type(ret, enc);
	}
	return ret;
}