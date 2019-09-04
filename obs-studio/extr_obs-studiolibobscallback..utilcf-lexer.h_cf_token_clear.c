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

/* Variables and functions */
 int /*<<< orphan*/  memset (struct cf_token*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void cf_token_clear(struct cf_token *t)
{
	memset(t, 0, sizeof(struct cf_token));
}