#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  TYPE_2__* sdlContentModelPtr ;
struct TYPE_6__ {TYPE_2__* group_ref; TYPE_2__* content; } ;
struct TYPE_7__ {int kind; TYPE_1__ u; } ;

/* Variables and functions */
#define  XSD_CONTENT_ALL 133 
#define  XSD_CONTENT_CHOICE 132 
#define  XSD_CONTENT_ELEMENT 131 
#define  XSD_CONTENT_GROUP 130 
#define  XSD_CONTENT_GROUP_REF 129 
#define  XSD_CONTENT_SEQUENCE 128 
 TYPE_2__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_hash_destroy (TYPE_2__*) ; 

void delete_model(zval *zv)
{
	sdlContentModelPtr tmp = Z_PTR_P(zv);
	switch (tmp->kind) {
		case XSD_CONTENT_ELEMENT:
		case XSD_CONTENT_GROUP:
			break;
		case XSD_CONTENT_SEQUENCE:
		case XSD_CONTENT_ALL:
		case XSD_CONTENT_CHOICE:
			zend_hash_destroy(tmp->u.content);
			efree(tmp->u.content);
			break;
		case XSD_CONTENT_GROUP_REF:
			efree(tmp->u.group_ref);
			break;
		default:
			break;
	}
	efree(tmp);
}