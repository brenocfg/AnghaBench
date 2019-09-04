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
struct cf_token {int dummy; } ;
struct cf_def {int /*<<< orphan*/  params; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct cf_token*) ; 

__attribute__((used)) static inline void cf_def_addparam(struct cf_def *cfd, struct cf_token *param)
{
	da_push_back(cfd->params, param);
}