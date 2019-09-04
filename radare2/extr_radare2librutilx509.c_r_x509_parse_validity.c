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
struct TYPE_8__ {scalar_t__ klass; scalar_t__ tag; scalar_t__ form; int /*<<< orphan*/  length; int /*<<< orphan*/  sector; TYPE_1__ list; } ;
struct TYPE_7__ {void* notAfter; void* notBefore; } ;
typedef  TYPE_2__ RX509Validity ;
typedef  TYPE_3__ RASN1Object ;

/* Variables and functions */
 scalar_t__ CLASS_UNIVERSAL ; 
 scalar_t__ FORM_CONSTRUCTED ; 
 scalar_t__ FORM_PRIMITIVE ; 
 scalar_t__ TAG_GENERALIZEDTIME ; 
 scalar_t__ TAG_SEQUENCE ; 
 scalar_t__ TAG_UTCTIME ; 
 void* r_asn1_stringify_time (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* r_asn1_stringify_utctime (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool r_x509_parse_validity(RX509Validity *validity, RASN1Object *object) {
	RASN1Object *o;
	if (!validity || !object || object->list.length != 2) {
		return false;
	}
	if (object->klass == CLASS_UNIVERSAL &&
		object->tag == TAG_SEQUENCE &&
		object->form == FORM_CONSTRUCTED) {
		o = object->list.objects[0];
		if (o->klass == CLASS_UNIVERSAL && o->form == FORM_PRIMITIVE) {
			if (o->tag == TAG_UTCTIME) {
				validity->notBefore = r_asn1_stringify_utctime (o->sector, o->length);
			} else if (o->tag == TAG_GENERALIZEDTIME) {
				validity->notBefore = r_asn1_stringify_time (o->sector, o->length);
			}
		}
		o = object->list.objects[1];
		if (o->klass == CLASS_UNIVERSAL && o->form == FORM_PRIMITIVE) {
			if (o->tag == TAG_UTCTIME) {
				validity->notAfter = r_asn1_stringify_utctime (o->sector, o->length);
			} else if (o->tag == TAG_GENERALIZEDTIME) {
				validity->notAfter = r_asn1_stringify_time (o->sector, o->length);
			}
		}
	}
	return true;
}