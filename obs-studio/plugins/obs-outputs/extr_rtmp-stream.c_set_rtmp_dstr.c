#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dstr {scalar_t__ len; int /*<<< orphan*/ * array; } ;
struct TYPE_3__ {int av_len; int /*<<< orphan*/ * av_val; } ;
typedef  TYPE_1__ AVal ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_is_empty (struct dstr*) ; 

__attribute__((used)) static inline void set_rtmp_dstr(AVal *val, struct dstr *str)
{
	bool valid = !dstr_is_empty(str);
	val->av_val = valid ? str->array : NULL;
	val->av_len = valid ? (int)str->len : 0;
}