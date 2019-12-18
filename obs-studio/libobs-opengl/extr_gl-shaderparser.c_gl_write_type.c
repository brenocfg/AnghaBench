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
struct gl_shader_parser {int /*<<< orphan*/  gl_string; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_cat (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  gl_write_type_n (struct gl_shader_parser*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static inline void gl_write_type(struct gl_shader_parser *glsp,
				 const char *type)
{
	if (!gl_write_type_n(glsp, type, strlen(type)))
		dstr_cat(&glsp->gl_string, type);
}