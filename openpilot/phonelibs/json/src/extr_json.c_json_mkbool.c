#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int bool_; } ;
typedef  TYPE_1__ JsonNode ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_BOOL ; 
 TYPE_1__* mknode (int /*<<< orphan*/ ) ; 

JsonNode *json_mkbool(bool b)
{
	JsonNode *ret = mknode(JSON_BOOL);
	ret->bool_ = b;
	return ret;
}