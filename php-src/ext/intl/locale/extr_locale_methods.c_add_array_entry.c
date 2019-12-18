#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_6__ {int /*<<< orphan*/ * val; } ;
typedef  TYPE_1__ zend_string ;

/* Variables and functions */
 int /*<<< orphan*/  DELIMITER ; 
 int /*<<< orphan*/  LOC_PRIVATE_TAG ; 
 int /*<<< orphan*/  LOC_VARIANT_TAG ; 
 int /*<<< orphan*/  add_assoc_str (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  add_assoc_string (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ ecalloc (int,int) ; 
 int /*<<< orphan*/  efree (char*) ; 
 TYPE_1__* get_icu_value_internal (char const*,char*,int*,int) ; 
 TYPE_1__* get_private_subtags (char const*) ; 
 char* php_strtok_r (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  zend_string_release_ex (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_array_entry(const char* loc_name, zval* hash_arr, char* key_name)
{
	zend_string*   key_value 	= NULL;
	char*   cur_key_name	= NULL;
	char*   token        	= NULL;
	char*   last_ptr  	= NULL;

	int	result		= 0;
	int 	cur_result  	= 0;


	if( strcmp(key_name , LOC_PRIVATE_TAG)==0 ){
		key_value = get_private_subtags( loc_name );
		result = 1;
	} else {
		key_value = get_icu_value_internal( loc_name , key_name , &result,1 );
	}
	if( (strcmp(key_name , LOC_PRIVATE_TAG)==0) ||
		( strcmp(key_name , LOC_VARIANT_TAG)==0) ){
		if( result > 0 && key_value){
			int cnt = 0;
			/* Tokenize on the "_" or "-"  */
			token = php_strtok_r( key_value->val , DELIMITER ,&last_ptr);
			if( cur_key_name ){
				efree( cur_key_name);
			}
			cur_key_name = (char*)ecalloc( 25,  25);
			sprintf( cur_key_name , "%s%d", key_name , cnt++);
			add_assoc_string( hash_arr, cur_key_name , token);
			/* tokenize on the "_" or "-" and stop  at singleton if any */
			while( (token = php_strtok_r(NULL , DELIMITER , &last_ptr)) && (strlen(token)>1) ){
				sprintf( cur_key_name , "%s%d", key_name , cnt++);
				add_assoc_string( hash_arr, cur_key_name , token);
			}
/*
			if( strcmp(key_name, LOC_PRIVATE_TAG) == 0 ){
			}
*/
		}
		if (key_value) {
			zend_string_release_ex(key_value, 0);
		}
	} else {
		if( result == 1 ){
			add_assoc_str( hash_arr, key_name , key_value);
			cur_result = 1;
		} else if (key_value) {
			zend_string_release_ex(key_value, 0);
		}
	}

	if( cur_key_name ){
		efree( cur_key_name);
	}
	/*if( key_name != LOC_PRIVATE_TAG && key_value){*/
	return cur_result;
}