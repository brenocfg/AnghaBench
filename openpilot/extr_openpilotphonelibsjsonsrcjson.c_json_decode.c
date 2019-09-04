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
 int /*<<< orphan*/  json_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_value (char const**,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  skip_space (char const**) ; 

JsonNode *json_decode(const char *json)
{
	const char *s = json;
	JsonNode *ret;
	
	skip_space(&s);
	if (!parse_value(&s, &ret))
		return NULL;
	
	skip_space(&s);
	if (*s != 0) {
		json_delete(ret);
		return NULL;
	}
	
	return ret;
}