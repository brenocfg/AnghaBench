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
struct dstr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_copy_dstr (struct dstr*,struct dstr const*) ; 
 int /*<<< orphan*/  dstr_init (struct dstr*) ; 

__attribute__((used)) static inline void dstr_init_copy_dstr(struct dstr *dst, const struct dstr *src)
{
	dstr_init(dst);
	dstr_copy_dstr(dst, src);
}