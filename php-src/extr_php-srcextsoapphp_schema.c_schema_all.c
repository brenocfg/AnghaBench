#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlAttrPtr ;
typedef  TYPE_3__* sdlTypePtr ;
typedef  int /*<<< orphan*/  sdlPtr ;
typedef  TYPE_4__* sdlContentModelPtr ;
typedef  int /*<<< orphan*/  sdlContentModel ;
struct TYPE_15__ {void* content; } ;
struct TYPE_18__ {TYPE_1__ u; int /*<<< orphan*/  kind; } ;
struct TYPE_17__ {TYPE_4__* model; } ;
struct TYPE_16__ {struct TYPE_16__* next; int /*<<< orphan*/  name; struct TYPE_16__* children; } ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  E_ERROR ; 
 int TRUE ; 
 int /*<<< orphan*/  XSD_CONTENT_ALL ; 
 int /*<<< orphan*/  delete_model ; 
 void* emalloc (int) ; 
 scalar_t__ node_is_equal (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  schema_element (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  schema_min_max (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  soap_error1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_init (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_next_index_insert_ptr (void*,TYPE_4__*) ; 

__attribute__((used)) static int schema_all(sdlPtr sdl, xmlAttrPtr tns, xmlNodePtr all, sdlTypePtr cur_type, sdlContentModelPtr model)
{
	xmlNodePtr trav;
	sdlContentModelPtr newModel;

	newModel = emalloc(sizeof(sdlContentModel));
	newModel->kind = XSD_CONTENT_ALL;
	newModel->u.content = emalloc(sizeof(HashTable));
	zend_hash_init(newModel->u.content, 0, NULL, delete_model, 0);
	if (model == NULL) {
		cur_type->model = newModel;
	} else {
		zend_hash_next_index_insert_ptr(model->u.content, newModel);
	}

	schema_min_max(all, newModel);

	trav = all->children;
	if (trav != NULL && node_is_equal(trav,"annotation")) {
		/* TODO: <annotation> support */
		trav = trav->next;
	}
	while (trav != NULL) {
		if (node_is_equal(trav,"element")) {
			schema_element(sdl, tns, trav, cur_type, newModel);
		} else {
			soap_error1(E_ERROR, "Parsing Schema: unexpected <%s> in all", trav->name);
		}
		trav = trav->next;
	}
	return TRUE;
}