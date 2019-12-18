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
struct TYPE_3__ {char* av_val; int av_len; } ;
typedef  TYPE_1__ AVal ;

/* Variables and functions */
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static inline void set_rtmp_str(AVal *val, const char *str)
{
	bool valid = (str && *str);
	val->av_val = valid ? (char *)str : NULL;
	val->av_len = valid ? (int)strlen(str) : 0;
}