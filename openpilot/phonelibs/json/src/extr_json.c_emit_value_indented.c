#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int tag; int /*<<< orphan*/  number_; int /*<<< orphan*/  string_; int /*<<< orphan*/  bool_; } ;
typedef  int /*<<< orphan*/  SB ;
typedef  TYPE_1__ JsonNode ;

/* Variables and functions */
#define  JSON_ARRAY 133 
#define  JSON_BOOL 132 
#define  JSON_NULL 131 
#define  JSON_NUMBER 130 
#define  JSON_OBJECT 129 
#define  JSON_STRING 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit_array_indented (int /*<<< orphan*/ *,TYPE_1__ const*,char const*,int) ; 
 int /*<<< orphan*/  emit_number (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_object_indented (int /*<<< orphan*/ *,TYPE_1__ const*,char const*,int) ; 
 int /*<<< orphan*/  emit_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_puts (int /*<<< orphan*/ *,char*) ; 
 int tag_is_valid (int) ; 

void emit_value_indented(SB *out, const JsonNode *node, const char *space, int indent_level)
{
	assert(tag_is_valid(node->tag));
	switch (node->tag) {
		case JSON_NULL:
			sb_puts(out, "null");
			break;
		case JSON_BOOL:
			sb_puts(out, node->bool_ ? "true" : "false");
			break;
		case JSON_STRING:
			emit_string(out, node->string_);
			break;
		case JSON_NUMBER:
			emit_number(out, node->number_);
			break;
		case JSON_ARRAY:
			emit_array_indented(out, node, space, indent_level);
			break;
		case JSON_OBJECT:
			emit_object_indented(out, node, space, indent_level);
			break;
		default:
			assert(false);
	}
}