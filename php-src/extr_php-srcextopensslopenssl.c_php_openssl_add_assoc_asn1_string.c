#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_3__ {int /*<<< orphan*/  length; scalar_t__ data; } ;
typedef  TYPE_1__ ASN1_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  add_assoc_stringl (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void php_openssl_add_assoc_asn1_string(zval * val, char * key, ASN1_STRING * str) /* {{{ */
{
	add_assoc_stringl(val, key, (char *)str->data, str->length);
}