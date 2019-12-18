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
typedef  int /*<<< orphan*/  zend_ulong ;
typedef  int zend_bool ;
typedef  scalar_t__ xmlNodePtr ;

/* Variables and functions */
 scalar_t__ SOAP_GLOBAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ Z_COUNTED_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_REFCOUNTED_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ref_map ; 
 int /*<<< orphan*/ * zend_hash_index_find (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_bool soap_check_xml_ref(zval *data, xmlNodePtr node)
{
	zval *data_ptr;

	if (SOAP_GLOBAL(ref_map)) {
		if ((data_ptr = zend_hash_index_find(SOAP_GLOBAL(ref_map), (zend_ulong)node)) != NULL) {
			if (!Z_REFCOUNTED_P(data) ||
			    !Z_REFCOUNTED_P(data_ptr) ||
			    Z_COUNTED_P(data) != Z_COUNTED_P(data_ptr)) {
				zval_ptr_dtor(data);
				ZVAL_COPY(data, data_ptr);
				return 1;
			}
		}
	}
	return 0;
}