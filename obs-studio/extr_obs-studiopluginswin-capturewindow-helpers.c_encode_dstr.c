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
 int /*<<< orphan*/  dstr_replace (struct dstr*,char*,char*) ; 

__attribute__((used)) static inline void encode_dstr(struct dstr *str)
{
	dstr_replace(str, "#", "#22");
	dstr_replace(str, ":", "#3A");
}