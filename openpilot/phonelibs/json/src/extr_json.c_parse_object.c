#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  JsonNode ;

/* Variables and functions */
 int /*<<< orphan*/  append_member (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  json_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_mkobject () ; 
 int /*<<< orphan*/  parse_string (char const**,char**) ; 
 int /*<<< orphan*/  parse_value (char const**,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  skip_space (char const**) ; 

__attribute__((used)) static bool parse_object(const char **sp, JsonNode **out)
{
	const char *s = *sp;
	JsonNode *ret = out ? json_mkobject() : NULL;
	char *key;
	JsonNode *value;
	
	if (*s++ != '{')
		goto failure;
	skip_space(&s);
	
	if (*s == '}') {
		s++;
		goto success;
	}
	
	for (;;) {
		if (!parse_string(&s, out ? &key : NULL))
			goto failure;
		skip_space(&s);
		
		if (*s++ != ':')
			goto failure_free_key;
		skip_space(&s);
		
		if (!parse_value(&s, out ? &value : NULL))
			goto failure_free_key;
		skip_space(&s);
		
		if (out)
			append_member(ret, key, value);
		
		if (*s == '}') {
			s++;
			goto success;
		}
		
		if (*s++ != ',')
			goto failure;
		skip_space(&s);
	}
	
success:
	*sp = s;
	if (out)
		*out = ret;
	return true;

failure_free_key:
	if (out)
		free(key);
failure:
	json_delete(ret);
	return false;
}