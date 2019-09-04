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
struct TYPE_8__ {int /*<<< orphan*/  length; int /*<<< orphan*/  sector; TYPE_1__ list; } ;
struct TYPE_7__ {int /*<<< orphan*/  content; int /*<<< orphan*/  contentType; } ;
typedef  TYPE_2__ RPKCS7ContentInfo ;
typedef  TYPE_3__ RASN1Object ;

/* Variables and functions */
 int /*<<< orphan*/  r_asn1_create_binary (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_asn1_stringify_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool r_pkcs7_parse_contentinfo(RPKCS7ContentInfo *ci, RASN1Object *object) {
	if (!ci || !object || object->list.length < 1 || !object->list.objects[0]) {
		return false;
	}
	ci->contentType = r_asn1_stringify_oid (object->list.objects[0]->sector, object->list.objects[0]->length);
	if (object->list.length > 1) {
		RASN1Object *obj1 = object->list.objects[1];
		if (obj1) {
			ci->content = r_asn1_create_binary (obj1->sector, obj1->length);
		}
	}
	return true;
}