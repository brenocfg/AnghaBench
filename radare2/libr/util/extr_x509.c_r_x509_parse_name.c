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
struct TYPE_6__ {size_t length; TYPE_3__** objects; } ;
struct TYPE_8__ {scalar_t__ klass; scalar_t__ tag; scalar_t__ form; int /*<<< orphan*/  length; int /*<<< orphan*/  sector; TYPE_1__ list; } ;
struct TYPE_7__ {size_t length; int /*<<< orphan*/ ** names; int /*<<< orphan*/ ** oids; } ;
typedef  TYPE_2__ RX509Name ;
typedef  int /*<<< orphan*/  RASN1String ;
typedef  TYPE_3__ RASN1Object ;

/* Variables and functions */
 scalar_t__ CLASS_UNIVERSAL ; 
 scalar_t__ FORM_CONSTRUCTED ; 
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ **) ; 
 scalar_t__ TAG_OID ; 
 scalar_t__ TAG_SEQUENCE ; 
 scalar_t__ TAG_SET ; 
 scalar_t__ calloc (size_t,int) ; 
 int /*<<< orphan*/ * r_asn1_stringify_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * r_asn1_stringify_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool r_x509_parse_name (RX509Name *name, RASN1Object *object) {
	ut32 i;
	if (!name || !object || !object->list.length) {
		return false;
	}
	if (object->klass == CLASS_UNIVERSAL && object->tag == TAG_SEQUENCE) {
		name->length = object->list.length;
		name->names = (RASN1String **)calloc (name->length, sizeof (RASN1String *));
		if (!name->names) {
			name->length = 0;
			return false;
		}
		name->oids = (RASN1String **)calloc (name->length, sizeof (RASN1String *));
		if (!name->oids) {
			name->length = 0;
			R_FREE (name->names);
			return false;
		}
		for (i = 0; i < object->list.length; ++i) {
			RASN1Object *o = object->list.objects[i];
			if (o && o->klass == CLASS_UNIVERSAL &&
				o->tag == TAG_SET &&
				o->form == FORM_CONSTRUCTED &&
				o->list.length == 1) {
				o = o->list.objects[0];
				if (o && o->list.length > 1 &&
					o->klass == CLASS_UNIVERSAL &&
					o->tag == TAG_SEQUENCE) {
					if (o->list.objects[0]->klass == CLASS_UNIVERSAL &&
						o->list.objects[0]->tag == TAG_OID) {
						name->oids[i] = r_asn1_stringify_oid (o->list.objects[0]->sector, o->list.objects[0]->length);
					}
					RASN1Object *obj1 = o->list.objects[1];
					if (obj1 && obj1->klass == CLASS_UNIVERSAL) {
						name->names[i] = r_asn1_stringify_string (obj1->sector, obj1->length);
					}
				}
			}
		}
	}
	return true;
}