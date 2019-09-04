#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_6__ {scalar_t__ data_len; char* data; } ;
typedef  TYPE_1__ libgdbr_t ;

/* Variables and functions */
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  isxdigit (char) ; 
 scalar_t__ r_str_startswith (char*,char*) ; 
 scalar_t__ read_packet (TYPE_1__*,int) ; 
 scalar_t__ send_ack (TYPE_1__*) ; 
 scalar_t__ send_msg (TYPE_1__*,char*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 scalar_t__ strtoull (char*,int /*<<< orphan*/ *,int) ; 

ut64 gdbr_get_baddr(libgdbr_t *g) {
	if (!g || send_msg (g, "qOffsets") < 0 || read_packet (g, false) < 0
	    || send_ack (g) < 0 || g->data_len == 0) {
		return UINT64_MAX;
	}
	ut64 off, min = UINT64_MAX;
	char *ptr;
	if (r_str_startswith (g->data, "TextSeg=")) {
		ptr = g->data + strlen ("TextSeg=");
		if (!isxdigit (*ptr)) {
			return min;
		}
		off = strtoull (ptr, NULL, 16);
		if (off < min) {
			min = off;
		}
		if (!(ptr = strchr (ptr, ';'))) {
			return min;
		}
		ptr++;
		if (*ptr && r_str_startswith (ptr, "DataSeg=")) {
			ptr += strlen ("DataSeg=");
			if (!isxdigit (*ptr)) {
				return min;
			}
			off = strtoull (ptr, NULL, 16);
			if (off < min) {
				min = off;
			}
		}
		return min;
	}
	if (!r_str_startswith (g->data, "Text=")) {
		return min;
	}
	ptr = g->data + strlen ("Text=");
	if (!isxdigit (*ptr)) {
		return min;
	}
	off = strtoull (ptr, NULL, 16);
	if (off < min) {
		min = off;
	}
	if (!(ptr = strchr (ptr, ';')) || !r_str_startswith (ptr + 1, "Data=")) {
		return UINT64_MAX;
	}
	ptr += strlen (";Data=");
	if (!isxdigit (*ptr)) {
		return UINT64_MAX;
	}
	off = strtoull (ptr, NULL, 16);
	if (off < min) {
		min = off;
	}
	if (!(ptr = strchr (ptr, ';'))) {
		return min;
	}
	ptr++;
	if (r_str_startswith (ptr, "Bss=")) {
		ptr += strlen ("Bss=");
		if (!isxdigit (*ptr)) {
			return min;
		}
		off = strtoull (ptr, NULL, 16);
		if (off < min) {
			min = off;
		}
	}
	return min;
}