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
typedef  size_t ut32 ;
struct TYPE_3__ {size_t length; int /*<<< orphan*/ * elements; } ;
typedef  TYPE_1__ RPKCS7Attributes ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_pkcs7_free_attribute (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r_pkcs7_free_attributes(RPKCS7Attributes *attributes) {
	ut32 i;
	if (attributes) {
		for (i = 0; i < attributes->length; ++i) {
			r_pkcs7_free_attribute (attributes->elements[i]);
		}
		R_FREE (attributes->elements);
		// Used internally pkcs #7, so it shouldn't free attributes.
	}
}