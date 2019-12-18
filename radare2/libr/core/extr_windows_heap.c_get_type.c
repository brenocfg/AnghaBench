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
typedef  int WPARAM ;

/* Variables and functions */
 int BACKEND_BLOCK ; 
 int LARGE_BLOCK ; 
#define  LF32_FIXED 130 
#define  LF32_FREE 129 
#define  LF32_MOVEABLE 128 
 int LFH_BLOCK ; 
 int NT_BLOCK ; 
 int SEGMENT_HEAP_BLOCK ; 
 int VS_BLOCK ; 
 char* r_str_newf (char*,char*,char*,char*) ; 

__attribute__((used)) static char *get_type(WPARAM flags) {
	char *state = "";
	switch (flags & 0xFFFF) {
	case LF32_FIXED:
		state = "(FIXED)";
		break;
	case LF32_FREE:
		state = "(FREE)";
		break;
	case LF32_MOVEABLE:
		state = "(MOVEABLE)";
		break;
	}
	char *heaptype = "";
	if (flags & SEGMENT_HEAP_BLOCK) {
		heaptype = "Segment";
	} else if (flags & NT_BLOCK) {
		heaptype =  "NT";
	}
	char *type = "";
	if (flags & LFH_BLOCK) {
		type = "/LFH";
	} else if (flags & LARGE_BLOCK) {
		type = "/LARGE";
	} else if (flags & BACKEND_BLOCK) {
		type = "/BACKEND";
	} else if (flags & VS_BLOCK) {
		type = "/VS";
	}
	return r_str_newf ("%s %s%s", state, heaptype, type);
}