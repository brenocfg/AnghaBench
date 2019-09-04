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
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  Sdb ;
typedef  void RBuffer ;
typedef  int /*<<< orphan*/  RBinFile ;

/* Variables and functions */
 int /*<<< orphan*/  check_buffer (void*) ; 
 void* r_buf_ref (void*) ; 

__attribute__((used)) static void *load_buffer(RBinFile *bf, RBuffer *buf, ut64 loadaddr, Sdb *sdb) {
	RBuffer *obj = r_buf_ref (buf);
	if (!check_buffer (obj)) {
		return NULL;
	}
	return obj;
}