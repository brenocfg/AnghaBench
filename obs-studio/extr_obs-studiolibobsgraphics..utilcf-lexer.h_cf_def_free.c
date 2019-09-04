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
struct cf_def {int /*<<< orphan*/  tokens; int /*<<< orphan*/  params; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  cf_token_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  da_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cf_def_free(struct cf_def *cfd)
{
	cf_token_clear(&cfd->name);
	da_free(cfd->params);
	da_free(cfd->tokens);
}