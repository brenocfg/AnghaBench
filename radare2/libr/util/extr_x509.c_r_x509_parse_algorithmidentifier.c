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
struct TYPE_9__ {int /*<<< orphan*/ * parameters; int /*<<< orphan*/  algorithm; } ;
struct TYPE_7__ {scalar_t__ klass; scalar_t__ tag; int /*<<< orphan*/  length; int /*<<< orphan*/  sector; } ;
typedef  TYPE_3__ RX509AlgorithmIdentifier ;
typedef  TYPE_4__ RASN1Object ;

/* Variables and functions */
 scalar_t__ CLASS_UNIVERSAL ; 
 scalar_t__ TAG_OID ; 
 int /*<<< orphan*/  r_asn1_stringify_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool r_x509_parse_algorithmidentifier (RX509AlgorithmIdentifier *ai, RASN1Object *object) {
	if (!ai || !object || object->list.length < 1 || !object->list.objects) {
		return false;
	}
	if (object->list.objects[0] && object->list.objects[0]->klass == CLASS_UNIVERSAL && object->list.objects[0]->tag == TAG_OID) {
		ai->algorithm = r_asn1_stringify_oid (object->list.objects[0]->sector, object->list.objects[0]->length);
	}
	ai->parameters = NULL; // TODO
	//ai->parameters = asn1_stringify_sector (object->list.objects[1]);
	return true;
}