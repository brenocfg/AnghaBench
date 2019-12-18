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
typedef  size_t ut8 ;
typedef  scalar_t__ ut64 ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 char* malloc (scalar_t__) ; 
 size_t r_buf_read8_at (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  r_buf_read_at (int /*<<< orphan*/ *,scalar_t__,size_t*,size_t) ; 

__attribute__((used)) static char *__read_nonnull_str_at(RBuffer *buf, ut64 offset) {
	ut8 sz = r_buf_read8_at (buf, offset);
	if (!sz) {
		return NULL;
	}
	char *str = malloc ((ut64)sz + 1);
	if (!str) {
		return NULL;
	}
	r_buf_read_at (buf, offset + 1, (ut8 *)str, sz);
	str[sz] = '\0';
	return str;
}