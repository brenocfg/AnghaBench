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
typedef  int /*<<< orphan*/  RStrBuf ;

/* Variables and functions */
 int /*<<< orphan*/  r_strbuf_appendf (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static void edf_pf_constraint(RStrBuf *result, const char *new_node_str) {
	r_strbuf_appendf (result, ":parity_of(%s)", new_node_str);
}