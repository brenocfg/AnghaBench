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
struct effect_parser {int /*<<< orphan*/  cfp; int /*<<< orphan*/ * cur_pass; int /*<<< orphan*/  tokens; int /*<<< orphan*/  files; int /*<<< orphan*/  techniques; int /*<<< orphan*/  samplers; int /*<<< orphan*/  funcs; int /*<<< orphan*/  structs; int /*<<< orphan*/  params; } ;

/* Variables and functions */
 int /*<<< orphan*/  cf_parser_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  da_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ep_init(struct effect_parser *ep)
{
	da_init(ep->params);
	da_init(ep->structs);
	da_init(ep->funcs);
	da_init(ep->samplers);
	da_init(ep->techniques);
	da_init(ep->files);
	da_init(ep->tokens);

	ep->cur_pass = NULL;
	cf_parser_init(&ep->cfp);
}