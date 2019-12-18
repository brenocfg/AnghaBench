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

/* Variables and functions */
 int /*<<< orphan*/  emit_string (int /*<<< orphan*/ *,char const*) ; 
 char* sb_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sb_init (int /*<<< orphan*/ *) ; 

char *json_encode_string(const char *str)
{
	SB sb;
	sb_init(&sb);
	
	emit_string(&sb, str);
	
	return sb_finish(&sb);
}