#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlAttrPtr ;
typedef  int /*<<< orphan*/  sdlTypePtr ;
typedef  int /*<<< orphan*/  sdlPtr ;
typedef  TYPE_2__* sdlContentModelPtr ;
typedef  int /*<<< orphan*/  sdlContentModel ;
struct TYPE_7__ {int /*<<< orphan*/  content; } ;
struct TYPE_8__ {TYPE_1__ u; int /*<<< orphan*/  kind; } ;

/* Variables and functions */
 int TRUE ; 
 int /*<<< orphan*/  XSD_CONTENT_ANY ; 
 TYPE_2__* emalloc (int) ; 
 int /*<<< orphan*/  schema_min_max (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  zend_hash_next_index_insert_ptr (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int schema_any(sdlPtr sdl, xmlAttrPtr tns, xmlNodePtr anyType, sdlTypePtr cur_type, sdlContentModelPtr model)
{
	if (model != NULL) {
		sdlContentModelPtr newModel;

		newModel = emalloc(sizeof(sdlContentModel));
		newModel->kind = XSD_CONTENT_ANY;

		schema_min_max(anyType, newModel);

		zend_hash_next_index_insert_ptr(model->u.content, newModel);
	}
	return TRUE;
}