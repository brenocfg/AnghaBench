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
typedef  enum wined3d_decl_usage { ____Placeholder_wined3d_decl_usage } wined3d_decl_usage ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  shader_semantic_name_from_usage (int) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

BOOL shader_match_semantic(const char *semantic_name, enum wined3d_decl_usage usage)
{
    return !strcmp(semantic_name, shader_semantic_name_from_usage(usage));
}