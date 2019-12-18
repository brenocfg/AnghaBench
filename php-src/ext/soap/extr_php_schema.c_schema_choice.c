#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlAttrPtr ;
typedef  TYPE_3__* sdlTypePtr ;
typedef  int /*<<< orphan*/  sdlPtr ;
typedef  TYPE_4__* sdlContentModelPtr ;
typedef  int /*<<< orphan*/  sdlContentModel ;
struct TYPE_24__ {void* content; } ;
struct TYPE_27__ {TYPE_1__ u; int /*<<< orphan*/  kind; } ;
struct TYPE_26__ {TYPE_4__* model; } ;
struct TYPE_25__ {struct TYPE_25__* next; int /*<<< orphan*/  name; struct TYPE_25__* children; } ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  E_ERROR ; 
 int TRUE ; 
 int /*<<< orphan*/  XSD_CONTENT_CHOICE ; 
 int /*<<< orphan*/  delete_model ; 
 void* emalloc (int) ; 
 scalar_t__ node_is_equal (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  schema_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  schema_element (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  schema_group (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  schema_min_max (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  schema_sequence (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  soap_error1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_init (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_next_index_insert_ptr (void*,TYPE_4__*) ; 

__attribute__((used)) static int schema_choice(sdlPtr sdl, xmlAttrPtr tns, xmlNodePtr choiceType, sdlTypePtr cur_type, sdlContentModelPtr model)
{
	xmlNodePtr trav;
	sdlContentModelPtr newModel;

	newModel = emalloc(sizeof(sdlContentModel));
	newModel->kind = XSD_CONTENT_CHOICE;
	newModel->u.content = emalloc(sizeof(HashTable));
	zend_hash_init(newModel->u.content, 0, NULL, delete_model, 0);
	if (model == NULL) {
		cur_type->model = newModel;
	} else {
		zend_hash_next_index_insert_ptr(model->u.content, newModel);
	}

	schema_min_max(choiceType, newModel);

	trav = choiceType->children;
	if (trav != NULL && node_is_equal(trav,"annotation")) {
		/* TODO: <annotation> support */
		trav = trav->next;
	}
	while (trav != NULL) {
		if (node_is_equal(trav,"element")) {
			schema_element(sdl, tns, trav, cur_type, newModel);
		} else if (node_is_equal(trav,"group")) {
			schema_group(sdl, tns, trav, cur_type, newModel);
		} else if (node_is_equal(trav,"choice")) {
			schema_choice(sdl, tns, trav, cur_type, newModel);
		} else if (node_is_equal(trav,"sequence")) {
			schema_sequence(sdl, tns, trav, cur_type, newModel);
		} else if (node_is_equal(trav,"any")) {
			schema_any(sdl, tns, trav, cur_type, newModel);
		} else {
			soap_error1(E_ERROR, "Parsing Schema: unexpected <%s> in choice", trav->name);
		}
		trav = trav->next;
	}
	return TRUE;
}