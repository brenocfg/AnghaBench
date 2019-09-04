#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* sdlTypePtr ;
typedef  TYPE_2__* sdlContentModelPtr ;
typedef  int /*<<< orphan*/  sdlContentModel ;
struct TYPE_5__ {void* group; int /*<<< orphan*/  group_ref; void* content; void* element; } ;
struct TYPE_6__ {int kind; int min_occurs; int max_occurs; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  WSDL_CACHE_GET_1 (int,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  WSDL_CACHE_GET_INT (int,char**) ; 
#define  XSD_CONTENT_ALL 133 
#define  XSD_CONTENT_CHOICE 132 
#define  XSD_CONTENT_ELEMENT 131 
#define  XSD_CONTENT_GROUP 130 
#define  XSD_CONTENT_GROUP_REF 129 
#define  XSD_CONTENT_SEQUENCE 128 
 int /*<<< orphan*/  delete_model ; 
 void* emalloc (int) ; 
 int /*<<< orphan*/  sdlContentKind ; 
 int /*<<< orphan*/  sdl_deserialize_string (char**) ; 
 int /*<<< orphan*/  zend_hash_init (void*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_next_index_insert_ptr (void*,TYPE_2__*) ; 

__attribute__((used)) static sdlContentModelPtr sdl_deserialize_model(sdlTypePtr *types, sdlTypePtr *elements, char **in)
{
	int i;
	sdlContentModelPtr model = emalloc(sizeof(sdlContentModel));

	WSDL_CACHE_GET_1(model->kind, sdlContentKind, in);
	WSDL_CACHE_GET_INT(model->min_occurs, in);
	WSDL_CACHE_GET_INT(model->max_occurs, in);
	switch (model->kind) {
		case XSD_CONTENT_ELEMENT:
			WSDL_CACHE_GET_INT(i, in);
			model->u.element = elements[i];
			break;
		case XSD_CONTENT_SEQUENCE:
		case XSD_CONTENT_ALL:
		case XSD_CONTENT_CHOICE:
			WSDL_CACHE_GET_INT(i, in);
			model->u.content = emalloc(sizeof(HashTable));
			zend_hash_init(model->u.content, i, NULL, delete_model, 0);
			while (i > 0) {
				sdlContentModelPtr x = sdl_deserialize_model(types, elements, in);
				zend_hash_next_index_insert_ptr(model->u.content, x);
				i--;
			}
			break;
		case XSD_CONTENT_GROUP_REF:
			model->u.group_ref = sdl_deserialize_string(in);
			break;
		case XSD_CONTENT_GROUP:
			WSDL_CACHE_GET_INT(i, in);
			model->u.group = types[i];
			break;
		default:
			break;
	}
	return model;
}