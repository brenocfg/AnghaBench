#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ RPKCS7Attribute ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  r_asn1_free_binary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_asn1_free_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r_pkcs7_free_attribute(RPKCS7Attribute *attribute) {
	if (attribute) {
		r_asn1_free_binary (attribute->data);
		r_asn1_free_string (attribute->oid);
		free (attribute);
	}
}