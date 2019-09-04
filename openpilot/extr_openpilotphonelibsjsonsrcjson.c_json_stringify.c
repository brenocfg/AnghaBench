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
typedef  int /*<<< orphan*/  SB ;
typedef  int /*<<< orphan*/  JsonNode ;

/* Variables and functions */
 int /*<<< orphan*/  emit_value (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  emit_value_indented (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ ) ; 
 char* sb_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sb_init (int /*<<< orphan*/ *) ; 

char *json_stringify(const JsonNode *node, const char *space)
{
	SB sb;
	sb_init(&sb);
	
	if (space != NULL)
		emit_value_indented(&sb, node, space, 0);
	else
		emit_value(&sb, node);
	
	return sb_finish(&sb);
}