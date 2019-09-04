#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ut32 ;
struct TYPE_6__ {scalar_t__ length; int /*<<< orphan*/ ** objects; } ;
struct TYPE_8__ {TYPE_1__ list; } ;
struct TYPE_7__ {size_t length; int /*<<< orphan*/ ** elements; } ;
typedef  int /*<<< orphan*/  RX509Certificate ;
typedef  TYPE_2__ RPKCS7ExtendedCertificatesAndCertificates ;
typedef  TYPE_3__ RASN1Object ;

/* Variables and functions */
 scalar_t__ calloc (scalar_t__,int) ; 
 int /*<<< orphan*/ * r_x509_parse_certificate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool r_pkcs7_parse_extendedcertificatesandcertificates(RPKCS7ExtendedCertificatesAndCertificates *ecac, RASN1Object *object) {
	ut32 i;
	if (!ecac || !object) {
		return false;
	}
	if (object->list.length > 0) {
		ecac->elements = (RX509Certificate **)calloc (object->list.length, sizeof (RX509Certificate *));
		if (!ecac->elements) {
			return false;
		}
		ecac->length = object->list.length;
		for (i = 0; i < ecac->length; ++i) {
			ecac->elements[i] = r_x509_parse_certificate (object->list.objects[i]);
			object->list.objects[i] = NULL;
		}
	}
	return true;
}