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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  RStrBuf ;

/* Variables and functions */
 int /*<<< orphan*/  r_strbuf_appendf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void decode_array(RStrBuf *sb, const ut8* start, const ut8* end) {
	while (start < end) {
		r_strbuf_appendf (sb, "%02x ", *start);
		start++;
	}
	r_strbuf_appendf (sb, "\n");
}