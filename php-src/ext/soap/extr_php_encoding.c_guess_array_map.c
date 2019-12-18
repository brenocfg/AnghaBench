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
typedef  int /*<<< orphan*/ * encodePtr ;

/* Variables and functions */
 int /*<<< orphan*/  APACHE_MAP ; 
 scalar_t__ IS_ARRAY ; 
 int /*<<< orphan*/  IS_NULL ; 
 int /*<<< orphan*/  SOAP_ENC_ARRAY ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_conversion (int /*<<< orphan*/ ) ; 
 scalar_t__ is_map (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  master_to_xml (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static xmlNodePtr guess_array_map(encodeTypePtr type, zval *data, int style, xmlNodePtr parent)
{
	encodePtr enc = NULL;

	if (data && Z_TYPE_P(data) == IS_ARRAY) {
		if (is_map(data)) {
			enc = get_conversion(APACHE_MAP);
		} else {
			enc = get_conversion(SOAP_ENC_ARRAY);
		}
	}
	if (!enc) {
		enc = get_conversion(IS_NULL);
	}

	return master_to_xml(enc, data, style, parent);
}