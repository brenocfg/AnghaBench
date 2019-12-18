#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  TYPE_3__* xmlNsPtr ;
typedef  TYPE_4__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
typedef  TYPE_5__* xmlAttrPtr ;
typedef  TYPE_6__* encodeTypePtr ;
typedef  TYPE_7__* encodePtr ;
struct TYPE_25__ {int /*<<< orphan*/  type; TYPE_2__* sdl_type; } ;
struct TYPE_26__ {TYPE_6__ details; } ;
struct TYPE_24__ {TYPE_1__* children; } ;
struct TYPE_23__ {scalar_t__ type; int /*<<< orphan*/  doc; struct TYPE_23__* next; struct TYPE_23__* children; scalar_t__ properties; } ;
struct TYPE_22__ {scalar_t__ href; } ;
struct TYPE_21__ {scalar_t__ kind; TYPE_7__* encode; } ;
struct TYPE_20__ {int /*<<< orphan*/ * content; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_CAST (char*) ; 
 int /*<<< orphan*/  IS_NULL ; 
 int /*<<< orphan*/  SOAP_ENC_ARRAY ; 
 int /*<<< orphan*/  SOAP_ENC_OBJECT ; 
 scalar_t__ SOAP_GLOBAL (int /*<<< orphan*/ ) ; 
 scalar_t__ XML_ELEMENT_NODE ; 
 int /*<<< orphan*/  XSD_STRING ; 
 scalar_t__ XSD_TYPEKIND_COMPLEX ; 
 int /*<<< orphan*/  XSI_NAMESPACE ; 
 int /*<<< orphan*/  ZVAL_COPY_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_TRY_DELREF_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_property_long (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_property_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  add_property_zval (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 TYPE_4__* check_and_resolve_href (TYPE_4__*) ; 
 int /*<<< orphan*/  efree (char*) ; 
 scalar_t__ get_attribute (scalar_t__,char*) ; 
 TYPE_5__* get_attribute_ex (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 TYPE_7__* get_conversion (int /*<<< orphan*/ ) ; 
 TYPE_7__* get_encoder_from_prefix (scalar_t__,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  master_to_zval_int (int /*<<< orphan*/ *,TYPE_7__*,TYPE_4__*) ; 
 int /*<<< orphan*/  object_init_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_namespace (int /*<<< orphan*/ *,char**,char**) ; 
 int /*<<< orphan*/  sdl ; 
 int /*<<< orphan*/  soap_var_class_entry ; 
 TYPE_3__* xmlSearchNs (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zval *guess_zval_convert(zval *ret, encodeTypePtr type, xmlNodePtr data)
{
	encodePtr enc = NULL;
	xmlAttrPtr tmpattr;
	xmlChar *type_name = NULL;

	data = check_and_resolve_href(data);

	if (data == NULL) {
		enc = get_conversion(IS_NULL);
	} else if (data->properties && get_attribute_ex(data->properties, "nil", XSI_NAMESPACE)) {
		enc = get_conversion(IS_NULL);
	} else {
		tmpattr = get_attribute_ex(data->properties,"type", XSI_NAMESPACE);
		if (tmpattr != NULL) {
		  type_name = tmpattr->children->content;
			enc = get_encoder_from_prefix(SOAP_GLOBAL(sdl), data, tmpattr->children->content);
			if (enc && type == &enc->details) {
				enc = NULL;
			}
			if (enc != NULL) {
			  encodePtr tmp = enc;
			  while (tmp &&
			         tmp->details.sdl_type != NULL &&
			         tmp->details.sdl_type->kind != XSD_TYPEKIND_COMPLEX) {
			    if (enc == tmp->details.sdl_type->encode ||
			        tmp == tmp->details.sdl_type->encode) {
			    	enc = NULL;
			    	break;
			    }
			    tmp = tmp->details.sdl_type->encode;
			  }
			}
		}

		if (enc == NULL) {
			/* Didn't have a type, totally guess here */
			/* Logic: has children = IS_OBJECT else IS_STRING */
			xmlNodePtr trav;

			if (get_attribute(data->properties, "arrayType") ||
			    get_attribute(data->properties, "itemType") ||
			    get_attribute(data->properties, "arraySize")) {
				enc = get_conversion(SOAP_ENC_ARRAY);
			} else {
				enc = get_conversion(XSD_STRING);
				trav = data->children;
				while (trav != NULL) {
					if (trav->type == XML_ELEMENT_NODE) {
						enc = get_conversion(SOAP_ENC_OBJECT);
						break;
					}
					trav = trav->next;
				}
			}
		}
	}
	master_to_zval_int(ret, enc, data);
	if (SOAP_GLOBAL(sdl) && type_name && enc->details.sdl_type) {
		zval soapvar;
		char *ns, *cptype;
		xmlNsPtr nsptr;

		object_init_ex(&soapvar, soap_var_class_entry);
		add_property_long(&soapvar, "enc_type", enc->details.type);
		Z_TRY_DELREF_P(ret);
		add_property_zval(&soapvar, "enc_value", ret);
		parse_namespace(type_name, &cptype, &ns);
		nsptr = xmlSearchNs(data->doc, data, BAD_CAST(ns));
		add_property_string(&soapvar, "enc_stype", cptype);
		if (nsptr) {
			add_property_string(&soapvar, "enc_ns", (char*)nsptr->href);
		}
		efree(cptype);
		if (ns) {efree(ns);}
		ZVAL_COPY_VALUE(ret, &soapvar);
	}
	return ret;
}