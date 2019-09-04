#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sdlTypePtr ;
typedef  TYPE_1__* sdlParamPtr ;
typedef  int /*<<< orphan*/  sdlParam ;
typedef  int /*<<< orphan*/  encodePtr ;
struct TYPE_3__ {int order; int /*<<< orphan*/  element; int /*<<< orphan*/  encode; int /*<<< orphan*/  paramName; } ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  WSDL_CACHE_GET_INT (int,char**) ; 
 int /*<<< orphan*/  delete_parameter ; 
 void* emalloc (int) ; 
 int /*<<< orphan*/  sdl_deserialize_key (int /*<<< orphan*/ *,TYPE_1__*,char**) ; 
 int /*<<< orphan*/  sdl_deserialize_string (char**) ; 
 int /*<<< orphan*/  zend_hash_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HashTable* sdl_deserialize_parameters(encodePtr *encoders, sdlTypePtr *types, char **in)
{
	int i, n;
	HashTable *ht;

	WSDL_CACHE_GET_INT(i, in);
	if (i == 0) {return NULL;}
	ht = emalloc(sizeof(HashTable));
	zend_hash_init(ht, i, NULL, delete_parameter, 0);
	while (i > 0) {
		sdlParamPtr param = emalloc(sizeof(sdlParam));
		sdl_deserialize_key(ht, param, in);
		param->paramName = sdl_deserialize_string(in);
		WSDL_CACHE_GET_INT(param->order, in);
		WSDL_CACHE_GET_INT(n, in);
		param->encode = encoders[n];
		WSDL_CACHE_GET_INT(n, in);
		param->element = types[n];
		--i;
	}
	return ht;
}