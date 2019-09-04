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
typedef  scalar_t__ xmlNodePtr ;

/* Variables and functions */
 scalar_t__ SOAP_GLOBAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ref_map ; 
 int /*<<< orphan*/  zend_hash_index_update (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void soap_add_xml_ref(zval *data, xmlNodePtr node)
{
	if (SOAP_GLOBAL(ref_map)) {
		zend_hash_index_update(SOAP_GLOBAL(ref_map), (zend_ulong)node, data);
	}
}