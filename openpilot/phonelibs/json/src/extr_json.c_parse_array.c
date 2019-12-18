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
 int /*<<< orphan*/  json_append_element (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_mkarray () ; 
 int /*<<< orphan*/  parse_value (char const**,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  skip_space (char const**) ; 

__attribute__((used)) static bool parse_array(const char **sp, JsonNode **out)
{
	const char *s = *sp;
	JsonNode *ret = out ? json_mkarray() : NULL;
	JsonNode *element;
	
	if (*s++ != '[')
		goto failure;
	skip_space(&s);
	
	if (*s == ']') {
		s++;
		goto success;
	}
	
	for (;;) {
		if (!parse_value(&s, out ? &element : NULL))
			goto failure;
		skip_space(&s);
		
		if (out)
			json_append_element(ret, element);
		
		if (*s == ']') {
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

failure:
	json_delete(ret);
	return false;
}