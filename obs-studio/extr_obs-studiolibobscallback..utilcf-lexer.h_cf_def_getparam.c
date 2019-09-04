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
struct cf_token {int dummy; } ;
struct TYPE_2__ {struct cf_token* array; } ;
struct cf_def {TYPE_1__ params; } ;

/* Variables and functions */

__attribute__((used)) static inline struct cf_token *cf_def_getparam(const struct cf_def *cfd,
		size_t idx)
{
	return cfd->params.array+idx;
}