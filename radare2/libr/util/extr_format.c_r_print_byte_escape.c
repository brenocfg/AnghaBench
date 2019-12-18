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
struct TYPE_3__ {int /*<<< orphan*/  esc_bslash; int /*<<< orphan*/  strconv_mode; } ;
typedef  TYPE_1__ RPrint ;

/* Variables and functions */
 int /*<<< orphan*/  r_return_if_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_str_byte_escape (char const*,char**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void r_print_byte_escape(const RPrint* p, const char *src, char **dst, int dot_nl) {
	r_return_if_fail (p->strconv_mode);
	r_str_byte_escape (src, dst, dot_nl, !strcmp (p->strconv_mode, "asciidot"), p->esc_bslash);
}