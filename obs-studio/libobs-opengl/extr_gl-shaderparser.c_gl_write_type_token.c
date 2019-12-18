#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gl_shader_parser {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  array; } ;
struct cf_token {TYPE_1__ str; } ;

/* Variables and functions */
 int gl_write_type_n (struct gl_shader_parser*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool gl_write_type_token(struct gl_shader_parser *glsp,
				       struct cf_token *token)
{
	return gl_write_type_n(glsp, token->str.array, token->str.len);
}