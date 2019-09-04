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
struct darray {int dummy; } ;
struct cf_token {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cf_token_clear (struct cf_token*) ; 
 int /*<<< orphan*/  darray_push_back (int,struct darray*,struct cf_token*) ; 

__attribute__((used)) static inline void append_end_token(struct darray *tokens)
{
	struct cf_token end;
	cf_token_clear(&end);
	darray_push_back(sizeof(struct cf_token), tokens, &end);
}