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
typedef  int /*<<< orphan*/  RListFree ;
typedef  int /*<<< orphan*/  RList ;
typedef  int /*<<< orphan*/  RBuffer ;
typedef  int /*<<< orphan*/  RBinSection ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * newSection (char*,int,int,int) ; 
 scalar_t__ r_bin_section_free ; 
 int /*<<< orphan*/  r_buf_read_at (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_list_newf (int /*<<< orphan*/ ) ; 
 int r_read_le32 (int /*<<< orphan*/ *) ; 
 char* r_str_ndup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_str_nlen (char const*,int) ; 

__attribute__((used)) static RList *parseSegments(RBuffer *buf, int off, int count) {
	ut8 *b = calloc (count, 32);
	(void)r_buf_read_at (buf, off, b, count * 32);
	int x = off;
	int X = 0;
	int i;
	RList *segments = r_list_newf ((RListFree)r_bin_section_free);
	if (!segments) {
		return NULL;
	}
	// eprintf ("Segments: %d\n", count);
	for (i = 0; i < count; i++) {
		int A = r_read_le32 (b + X + 16);
		int B = r_read_le32 (b + X + 16 + 8);
		//	eprintf ("0x%08x  segment  0x%08x 0x%08x  %s\n",
		//		x, A, A + B, b + X);
		const char *cname = (const char *)(b + X);
		char *name = r_str_ndup (cname, r_str_nlen (cname, 16));
		RBinSection *section = newSection (name, A, A + B, true);
		free (name);
		r_list_append (segments, section);
		x += 32;
		X += 32;
	}
	return segments;
}