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
struct shader_parser {int /*<<< orphan*/  funcs; int /*<<< orphan*/  samplers; int /*<<< orphan*/  structs; int /*<<< orphan*/  params; int /*<<< orphan*/  cfp; } ;

/* Variables and functions */
 int /*<<< orphan*/  cf_parser_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  da_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void shader_parser_init(struct shader_parser *sp)
{
	cf_parser_init(&sp->cfp);

	da_init(sp->params);
	da_init(sp->structs);
	da_init(sp->samplers);
	da_init(sp->funcs);
}