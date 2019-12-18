#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_4__ {int data_len; float* data; } ;
typedef  TYPE_1__ libgdbr_t ;

/* Variables and functions */
 int /*<<< orphan*/  isxdigit (char) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  send_ack (TYPE_1__*) ; 
 int sscanf (char*,char*,int*) ; 
 char* strchr (char*,char) ; 

int handle_vFile_pread(libgdbr_t *g, ut8 *buf) {
	send_ack (g);
	char *ptr;
	int len;
	if (g->data_len < 3 || g->data[0] != 'F') {
		return -1;
	}
	// F-1 is an error, yes, but it probably should not be fatal, since it might
	// mean we're reading beyond file end. So this is handled in gdbr_read_file
	if (g->data[1] == '-') {
		return 0;
	}
	if (!isxdigit (g->data[1])) {
		return -1;
	}
	if (sscanf (g->data, "F%x;", &len) != 1) {
		return -1;
	}
	// Again, this is probably the end of file
	if (len == 0) {
		return 0;
	}
	if (!(ptr = strchr (g->data, ';')) || ptr >= g->data + g->data_len) {
		return -1;
	}
	ptr++;
	if (len > 0) {
		memcpy (buf, ptr, len);
	}
	return len;
}