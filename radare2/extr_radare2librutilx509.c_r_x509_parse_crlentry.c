#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int length; TYPE_1__** objects; } ;
struct TYPE_10__ {TYPE_2__ list; } ;
struct TYPE_9__ {int /*<<< orphan*/  revocationDate; int /*<<< orphan*/  userCertificate; } ;
struct TYPE_7__ {int /*<<< orphan*/  length; int /*<<< orphan*/  sector; } ;
typedef  TYPE_3__ RX509CRLEntry ;
typedef  TYPE_4__ RASN1Object ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  r_asn1_create_binary (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_asn1_stringify_utctime (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

RX509CRLEntry *r_x509_parse_crlentry (RASN1Object *object) {
	RX509CRLEntry *entry;
	if (!object || object->list.length != 2) {
		return NULL;
	}
	entry = (RX509CRLEntry *)malloc (sizeof (RX509CRLEntry));
	if (!entry) {
		return NULL;
	}
	entry->userCertificate = r_asn1_create_binary (object->list.objects[0]->sector, object->list.objects[0]->length);
	entry->revocationDate = r_asn1_stringify_utctime (object->list.objects[1]->sector, object->list.objects[1]->length);
	return entry;
}