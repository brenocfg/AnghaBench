#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  TYPE_4__* xmlNodePtr ;
typedef  TYPE_5__* xmlAttrPtr ;
typedef  TYPE_6__* encodePtr ;
struct TYPE_19__ {TYPE_2__* sdl_type; } ;
struct TYPE_22__ {TYPE_3__ details; } ;
struct TYPE_21__ {TYPE_1__* children; } ;
struct TYPE_20__ {int /*<<< orphan*/  properties; } ;
struct TYPE_18__ {scalar_t__ kind; TYPE_6__* encode; } ;
struct TYPE_17__ {int /*<<< orphan*/  content; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOAP_GLOBAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNKNOWN_TYPE ; 
 scalar_t__ XSD_TYPEKIND_COMPLEX ; 
 int /*<<< orphan*/  XSI_NAMESPACE ; 
 TYPE_4__* check_and_resolve_href (TYPE_4__*) ; 
 TYPE_5__* get_attribute_ex (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_6__* get_conversion (int /*<<< orphan*/ ) ; 
 TYPE_6__* get_encoder_from_prefix (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * master_to_zval_int (int /*<<< orphan*/ *,TYPE_6__*,TYPE_4__*) ; 
 int /*<<< orphan*/  sdl ; 

zval *master_to_zval(zval *ret, encodePtr encode, xmlNodePtr data)
{
	data = check_and_resolve_href(data);

	if (encode == NULL) {
		encode = get_conversion(UNKNOWN_TYPE);
	} else {
		/* Use xsi:type if it is defined */
		xmlAttrPtr type_attr = get_attribute_ex(data->properties,"type", XSI_NAMESPACE);

		if (type_attr != NULL) {
			encodePtr  enc = get_encoder_from_prefix(SOAP_GLOBAL(sdl), data, type_attr->children->content);

			if (enc != NULL && enc != encode) {
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
			  if (enc != NULL) {
			    encode = enc;
			  }
			}
		}
	}
	return master_to_zval_int(ret, encode, data);
}