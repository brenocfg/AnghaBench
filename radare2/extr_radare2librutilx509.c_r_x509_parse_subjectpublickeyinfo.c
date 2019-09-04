#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int length; TYPE_3__** objects; } ;
struct TYPE_9__ {int /*<<< orphan*/  length; TYPE_1__ list; int /*<<< orphan*/  sector; } ;
struct TYPE_8__ {void* subjectPublicKeyModule; void* subjectPublicKeyExponent; void* subjectPublicKey; int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_2__ RX509SubjectPublicKeyInfo ;
typedef  TYPE_3__ RASN1Object ;

/* Variables and functions */
 void* r_asn1_create_binary (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_x509_parse_algorithmidentifier (int /*<<< orphan*/ *,TYPE_3__*) ; 

bool r_x509_parse_subjectpublickeyinfo (RX509SubjectPublicKeyInfo *spki, RASN1Object *object) {
	RASN1Object *o;
	if (!spki || !object || object->list.length != 2) {
		return false;
	}
	r_x509_parse_algorithmidentifier (&spki->algorithm, object->list.objects[0]);
	if (object->list.objects[1]) {
		o = object->list.objects[1];
		spki->subjectPublicKey = r_asn1_create_binary (o->sector, o->length);
		if (o->list.length == 1 && o->list.objects[0] && o->list.objects[0]->list.length == 2) {
			o = o->list.objects[0];
			if (o->list.objects[0]) {
				spki->subjectPublicKeyExponent = r_asn1_create_binary (o->list.objects[0]->sector, o->list.objects[0]->length);
			}
			if (o->list.objects[1]) {
				spki->subjectPublicKeyModule = r_asn1_create_binary (o->list.objects[1]->sector, o->list.objects[1]->length);
			}
		}
	}
	return true;
}