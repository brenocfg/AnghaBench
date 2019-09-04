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
struct TYPE_6__ {int length; TYPE_3__** objects; } ;
struct TYPE_8__ {scalar_t__ tag; scalar_t__* sector; int /*<<< orphan*/  length; TYPE_1__ list; } ;
struct TYPE_7__ {int critical; int /*<<< orphan*/  extnValue; int /*<<< orphan*/  extnID; } ;
typedef  TYPE_2__ RX509Extension ;
typedef  TYPE_3__ RASN1Object ;

/* Variables and functions */
 scalar_t__ TAG_BOOLEAN ; 
 scalar_t__ TAG_OCTETSTRING ; 
 scalar_t__ TAG_OID ; 
 int /*<<< orphan*/  r_asn1_create_binary (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_asn1_stringify_oid (scalar_t__*,int /*<<< orphan*/ ) ; 

bool r_x509_parse_extension (RX509Extension *ext, RASN1Object *object) {
	RASN1Object *o;
	if (!ext || !object || object->list.length < 2) {
		return false;
	}
	o = object->list.objects[0];
	if (o && o->tag == TAG_OID) {
		ext->extnID = r_asn1_stringify_oid (o->sector, o->length);
		o = object->list.objects[1];
		if (o->tag == TAG_BOOLEAN && object->list.length > 2) {
			//This field is optional (so len must be 3)
			ext->critical = o->sector[0] != 0;
			o = object->list.objects[2];
		}
		if (o->tag == TAG_OCTETSTRING) {
			ext->extnValue = r_asn1_create_binary (o->sector, o->length);
		}
	}
	return true;
}