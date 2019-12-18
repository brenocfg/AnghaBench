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
typedef  int /*<<< orphan*/  xmlNodePtr ;
typedef  int /*<<< orphan*/  encodeTypePtr ;
typedef  int /*<<< orphan*/  encodePtr ;

/* Variables and functions */
 int /*<<< orphan*/  IS_NULL ; 
 int /*<<< orphan*/  Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_conversion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  master_to_xml_int (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static xmlNodePtr guess_xml_convert(encodeTypePtr type, zval *data, int style, xmlNodePtr parent)
{
	encodePtr  enc;
	xmlNodePtr ret;

	if (data) {
		enc = get_conversion(Z_TYPE_P(data));
	} else {
		enc = get_conversion(IS_NULL);
	}
	ret = master_to_xml_int(enc, data, style, parent, 0);
/*
	if (style == SOAP_LITERAL && SOAP_GLOBAL(sdl)) {
		set_ns_and_type(ret, &enc->details);
	}
*/
	return ret;
}