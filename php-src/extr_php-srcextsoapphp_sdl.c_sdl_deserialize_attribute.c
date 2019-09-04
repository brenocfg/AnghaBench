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
typedef  TYPE_1__* sdlExtraAttributePtr ;
typedef  int /*<<< orphan*/  sdlExtraAttribute ;
typedef  TYPE_2__* sdlAttributePtr ;
typedef  int /*<<< orphan*/  encodePtr ;
struct TYPE_6__ {void* extraAttributes; int /*<<< orphan*/  encode; int /*<<< orphan*/  use; int /*<<< orphan*/  form; void* fixed; void* def; void* ref; void* namens; void* name; } ;
struct TYPE_5__ {void* val; void* ns; } ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  WSDL_CACHE_GET_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  WSDL_CACHE_GET_INT (int,char**) ; 
 int /*<<< orphan*/  delete_extra_attribute ; 
 void* emalloc (int) ; 
 int /*<<< orphan*/  sdlForm ; 
 int /*<<< orphan*/  sdlUse ; 
 int /*<<< orphan*/  sdl_deserialize_key (void*,TYPE_1__*,char**) ; 
 void* sdl_deserialize_string (char**) ; 
 int /*<<< orphan*/  zend_hash_init (void*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdl_deserialize_attribute(sdlAttributePtr attr, encodePtr *encoders, char **in)
{
	int i;

	attr->name = sdl_deserialize_string(in);
	attr->namens = sdl_deserialize_string(in);
	attr->ref = sdl_deserialize_string(in);
	attr->def = sdl_deserialize_string(in);
	attr->fixed = sdl_deserialize_string(in);
	WSDL_CACHE_GET_1(attr->form, sdlForm, in);
	WSDL_CACHE_GET_1(attr->use, sdlUse, in);
	WSDL_CACHE_GET_INT(i, in);
	attr->encode = encoders[i];
	WSDL_CACHE_GET_INT(i, in);
	if (i > 0) {
		attr->extraAttributes = emalloc(sizeof(HashTable));
		zend_hash_init(attr->extraAttributes, i, NULL, delete_extra_attribute, 0);
		while (i > 0) {
			sdlExtraAttributePtr x = emalloc(sizeof(sdlExtraAttribute));
			sdl_deserialize_key(attr->extraAttributes, x, in);
			x->ns = sdl_deserialize_string(in);
			x->val = sdl_deserialize_string(in);
			--i;
		}
	}
}