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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut32 ;
typedef  int /*<<< orphan*/  RX509Certificate ;
typedef  int /*<<< orphan*/  RASN1Object ;

/* Variables and functions */
 int /*<<< orphan*/ * r_asn1_create_object (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * r_x509_parse_certificate (int /*<<< orphan*/ *) ; 

RX509Certificate *r_x509_parse_certificate2 (const ut8 *buffer, ut32 length) {
	RX509Certificate *certificate;
	RASN1Object *object;
	if (!buffer || !length) {
		return NULL;
	}
	object = r_asn1_create_object (buffer, length, buffer);
	certificate = r_x509_parse_certificate (object);
	//object freed by r_x509_parse_certificate
	return certificate;
}