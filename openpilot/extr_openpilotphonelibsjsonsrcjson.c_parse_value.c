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
 int /*<<< orphan*/  expect_literal (char const**,char*) ; 
 int /*<<< orphan*/ * json_mkbool (int) ; 
 int /*<<< orphan*/ * json_mknull () ; 
 int /*<<< orphan*/ * json_mknumber (double) ; 
 int /*<<< orphan*/ * mkstring (char*) ; 
 int /*<<< orphan*/  parse_array (char const**,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  parse_number (char const**,double*) ; 
 int /*<<< orphan*/  parse_object (char const**,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  parse_string (char const**,char**) ; 

__attribute__((used)) static bool parse_value(const char **sp, JsonNode **out)
{
	const char *s = *sp;
	
	switch (*s) {
		case 'n':
			if (expect_literal(&s, "null")) {
				if (out)
					*out = json_mknull();
				*sp = s;
				return true;
			}
			return false;
		
		case 'f':
			if (expect_literal(&s, "false")) {
				if (out)
					*out = json_mkbool(false);
				*sp = s;
				return true;
			}
			return false;
		
		case 't':
			if (expect_literal(&s, "true")) {
				if (out)
					*out = json_mkbool(true);
				*sp = s;
				return true;
			}
			return false;
		
		case '"': {
			char *str;
			if (parse_string(&s, out ? &str : NULL)) {
				if (out)
					*out = mkstring(str);
				*sp = s;
				return true;
			}
			return false;
		}
		
		case '[':
			if (parse_array(&s, out)) {
				*sp = s;
				return true;
			}
			return false;
		
		case '{':
			if (parse_object(&s, out)) {
				*sp = s;
				return true;
			}
			return false;
		
		default: {
			double num;
			if (parse_number(&s, out ? &num : NULL)) {
				if (out)
					*out = json_mknumber(num);
				*sp = s;
				return true;
			}
			return false;
		}
	}
}