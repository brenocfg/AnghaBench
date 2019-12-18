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
struct TYPE_6__ {scalar_t__ length; int /*<<< orphan*/ * objects; } ;
struct TYPE_8__ {TYPE_1__ list; } ;
struct TYPE_7__ {size_t length; int /*<<< orphan*/ ** elements; } ;
typedef  int /*<<< orphan*/  RX509CertificateRevocationList ;
typedef  TYPE_2__ RPKCS7CertificateRevocationLists ;
typedef  TYPE_3__ RASN1Object ;

/* Variables and functions */
 scalar_t__ calloc (size_t,int) ; 
 int /*<<< orphan*/ * r_x509_parse_crl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool r_pkcs7_parse_certificaterevocationlists(RPKCS7CertificateRevocationLists *crls, RASN1Object *object) {
	ut32 i;
	if (!crls || !object) {
		return false;
	}
	if (object->list.length > 0) {
		crls->elements = (RX509CertificateRevocationList **)calloc (object->list.length, sizeof (RX509CertificateRevocationList *));
		if (!crls->elements) {
			return false;
		}
		crls->length = object->list.length;
		for (i = 0; i < crls->length; ++i) {
			crls->elements[i] = r_x509_parse_crl (object->list.objects[i]);
		}
	}
	return true;
}