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
typedef  scalar_t__ ut32 ;
typedef  int /*<<< orphan*/  RStrBuf ;

/* Variables and functions */
 int /*<<< orphan*/  r_strbuf_appendf (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void pad(RStrBuf *sb, ut32 count) {
	ut32 i;
	for (i = 0; i < count; i++) {
		r_strbuf_appendf (sb, "    ");
	}
}